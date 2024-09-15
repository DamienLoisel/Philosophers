/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:54:58 by dloisel           #+#    #+#             */
/*   Updated: 2024/08/09 15:15:32 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	res;
	int		signe;

	i = 0;
	res = 0;
	signe = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i + 1] == '+' || nptr[i + 1] == '-')
			return (-1);
		else if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	while ((nptr[i] != '\0') && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (res > 2147483647 || res < -2147483648)
		return (-1);
	return (res * signe);
}

int	ft_arg_parsing(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf(RED"The program must take these following arguments :\n");
		printf("- number_of_philosophers.\n");
		printf("- time_to_die (in milliseconds).\n");
		printf("- time_to_eat (in milliseconds).\n");
		printf("- time_to_sleep (in milliseconds).\n");
		printf("- nb_of_times_each_philosopher_must_eat (optional).\n"RESET);
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return \
				(printf(RED"All arguments must be positive integers."RESET), 0);
		}
	}
	return (1);
}

int	ft_struct_init(t_p *philo, char **argv)
{
	philo->philo_info.nb_philo = ft_atoi(argv[1]);
	philo->philo_info.time_to_die = ft_atoi(argv[2]);
	philo->philo_info.time_to_eat = ft_atoi(argv[3]);
	philo->philo_info.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->philo_info.nb_to_eat = ft_atoi(argv[5]);
	else
		philo->philo_info.nb_to_eat = -1;
	if (philo->philo_info.nb_philo <= 0 || philo->philo_info.time_to_die <= 0 \
	|| philo->philo_info.time_to_eat <= 0 \
	|| philo->philo_info.time_to_sleep <= 0)
		return (printf(RED"Invalid argument.\n"RESET), 0);
	return (1);
}

int	ft_init_mutex(t_p *philo)
{
	if (pthread_mutex_init(&philo->philo_info.write_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&philo->philo_info.eat_mutex, NULL))
	{
		pthread_mutex_destroy(&philo->philo_info.write_mutex);
		return (0);
	}
	if (pthread_mutex_init(&philo->philo_info.is_dead_mutex, NULL))
	{
		pthread_mutex_destroy(&philo->philo_info.write_mutex);
		pthread_mutex_destroy(&philo->philo_info.eat_mutex);
		return (0);
	}
	return (1);
}
