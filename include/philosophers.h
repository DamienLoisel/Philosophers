/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:45:07 by dloisel           #+#    #+#             */
/*   Updated: 2024/08/09 15:15:42 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef struct s_philo_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	long int		start_time;
	int				stop;
	int				is_dead;
	int				is_full;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	is_dead_mutex;
}	t_philo_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_t		death_thread_id;
	long int		last_meal;
	int				nb_of_meals;
	t_philo_info	*info;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

typedef struct s_p
{
	t_philo_info	philo_info;
	t_philo			*philosopher;
}	t_p;

//program_init
int			ft_arg_parsing(int argc, char **argv);
int			ft_struct_init(t_p *philo, char **argv);
int			ft_init_mutex(t_p *philo);

//philo_create
int			ft_philo_create(t_p *philo);
int			ft_philo_create_threads(t_p *philo);

//philo_threads
void		*philosopher_routine(void *arg);
void		philosopher_fork_eat(t_philo *philo);
void		philosopher_fork_eat2(t_philo *philo);
void		philosopher_sleep_think(t_philo *philo);
void		*death_watcher(void *arg);

//utils1
long int	ft_get_time(void);
void		ft_usleep(long int sleep_time);
void		ft_display_status(char *str, t_philo *philo);

#endif
