/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien_loisel <damien_loisel@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:44:46 by dloisel           #+#    #+#             */
/*   Updated: 2024/08/09 18:48:36 by damien_lois      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_thread_finish(t_p *philo)
{
	int	i;

	i = -1;
	while (++i < philo->philo_info.nb_philo)
		pthread_join(philo->philosopher[i].thread_id, NULL);
	if (philo->philo_info.is_full == philo->philo_info.nb_philo \
	&& philo->philo_info.nb_to_eat > 0)
		printf(RED"All philosophers have eaten %d time(s)\n"RESET, \
		philo->philo_info.nb_to_eat);
	i = -1;
	while (++i < philo->philo_info.nb_philo)
		pthread_mutex_destroy(&philo->philosopher[i].l_fork);
	pthread_mutex_destroy(&philo->philo_info.write_mutex);
	pthread_mutex_destroy(&philo->philo_info.eat_mutex);
	pthread_mutex_destroy(&philo->philo_info.is_dead_mutex);
	free(philo->philosopher);
}

int	main(int argc, char **argv)
{
	t_p	philo;

	if (!ft_arg_parsing(argc, argv) || !ft_struct_init(&philo, argv))
		return (1);
	philo.philosopher = malloc(sizeof(t_philo) * philo.philo_info.nb_philo);
	if (philo.philosopher == NULL)
		return (1);
	if (!ft_philo_create(&philo))
		free(philo.philosopher);
	ft_thread_finish(&philo);
	return (0);
}
