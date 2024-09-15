/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:46:23 by dloisel           #+#    #+#             */
/*   Updated: 2024/09/14 18:07:14 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	ft_get_time(void)
{
	long int		res;
	struct timeval	current_time;

	res = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (printf("Error with gettimeofday\n"), exit(1), 0);
	res = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (res);
}

void	ft_usleep(long int sleep_time)
{
	long int	start_time;

	start_time = ft_get_time();
	while (ft_get_time() - start_time < sleep_time)
		usleep(sleep_time / 100);
}

void	ft_display_status(char *str, t_philo *philo)
{
	long int	actual_time;
	long int	status_time;

	pthread_mutex_lock(&philo->info->is_dead_mutex);
	if (!philo->info->is_dead && \
	philo->info->is_full != philo->info->nb_philo)
	{
		actual_time = ft_get_time();
		status_time = actual_time - philo->info->start_time;
		printf(YELLOW"%ld\t"RESET, status_time);
		printf(GREEN"%d "RESET, philo->id);
		printf(BLUE"%s"RESET, str);
	}
	pthread_mutex_unlock(&philo->info->is_dead_mutex);
}
