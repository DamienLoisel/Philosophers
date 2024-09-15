/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:28:36 by dloisel           #+#    #+#             */
/*   Updated: 2024/08/11 14:21:06 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_philo_create(t_p *philo)
{
	int	i;

	i = -1;
	philo->philo_info.start_time = ft_get_time();
	philo->philo_info.stop = 0;
	philo->philo_info.is_dead = 0;
	philo->philo_info.is_full = 0;
	if (!ft_init_mutex(philo))
		return (0);
	while (++i < philo->philo_info.nb_philo)
	{
		philo->philosopher[i].id = i + 1;
		philo->philosopher[i].nb_of_meals = 0;
		philo->philosopher[i].last_meal = philo->philo_info.start_time;
		philo->philosopher[i].info = &philo->philo_info;
		pthread_mutex_init(&philo->philosopher[i].l_fork, NULL);
		if (i == (philo->philo_info.nb_philo - 1))
			philo->philosopher[i].r_fork = &philo->philosopher[0].l_fork;
		else
			philo->philosopher[i].r_fork = &philo->philosopher[i + 1].l_fork;
	}
	if (!ft_philo_create_threads(philo))
		return (0);
	return (1);
}

int	ft_philo_create_threads(t_p *philo)
{
	int	i;

	i = 0;
	if (philo->philo_info.nb_to_eat == 0)
		return (0);
	else
	{
		while (i < philo->philo_info.nb_philo)
		{
			if (pthread_create(&philo->philosopher[i].thread_id, NULL, \
			philosopher_routine, &philo->philosopher[i]) != 0)
			{
				printf("Couldn't create thread\n");
				return (0);
			}
			i++;
		}
	}
	return (1);
}
