/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:24:54 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/14 18:06:54 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat / 2);
	pthread_create(&philo->death_thread_id, NULL, death_watcher, arg);
	pthread_mutex_lock(&philo->info->is_dead_mutex);
	while (!philo->info->is_dead)
	{
		pthread_mutex_unlock(&philo->info->is_dead_mutex);
		philosopher_fork_eat(philo);
		philo->nb_of_meals++;
		if (philo->nb_of_meals == philo->info->nb_to_eat)
		{
			pthread_mutex_lock(&philo->info->is_dead_mutex);
			philo->info->is_full++;
			break ;
		}
		pthread_mutex_lock(&philo->info->is_dead_mutex);
	}
	pthread_mutex_unlock(&philo->info->is_dead_mutex);
	pthread_join(philo->death_thread_id, NULL);
	return (NULL);
}

void	*death_watcher(void *arg)
{
	t_philo	*philo;
	long	should_die;

	philo = (t_philo *)arg;
	ft_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->eat_mutex);
	should_die = (ft_get_time() - philo->last_meal);
	pthread_mutex_unlock(&philo->info->eat_mutex);
	if (should_die >= (long)philo->info->time_to_die)
	{
		pthread_mutex_lock(&philo->info->write_mutex);
		ft_display_status("died\n", philo);
		pthread_mutex_unlock(&philo->info->write_mutex);
		pthread_mutex_lock(&philo->info->is_dead_mutex);
		philo->info->is_dead = 1;
		pthread_mutex_unlock(&philo->info->is_dead_mutex);
		return (NULL);
	}
	return (NULL);
}

void	philosopher_fork_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->info->write_mutex);
	ft_display_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->info->write_mutex);
	if (!philo->r_fork || philo->r_fork == &philo->l_fork)
	{
		ft_usleep(philo->info->time_to_die + 1);
		pthread_mutex_unlock(&philo->l_fork);
		return ;
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(&philo->l_fork);
	philosopher_fork_eat2(philo);
}

void	philosopher_fork_eat2(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->write_mutex);
	ft_display_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->info->write_mutex);
	pthread_mutex_lock(&philo->info->write_mutex);
	ft_display_status("is eating\n", philo);
	pthread_mutex_unlock(&philo->info->write_mutex);
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->info->eat_mutex);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philosopher_sleep_think(philo);
}

void	philosopher_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->write_mutex);
	ft_display_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->info->write_mutex);
	ft_usleep(philo->info->time_to_sleep);
	pthread_mutex_lock(&philo->info->write_mutex);
	ft_display_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->info->write_mutex);
}
