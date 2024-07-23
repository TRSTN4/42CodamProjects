/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <tvan-bee@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/08 12:18:16 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/20 21:15:46 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct l_philo
{
	int				id;
	int				times_eaten;
	long int		last_time_eaten;
	pthread_t		thread;
	struct l_config	*config;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}		t_philo;

typedef struct l_config
{
	int				philos_finished_eating;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal;
	int				stop;
	long int		start_time;
	t_philo			*philo;
	pthread_mutex_t	lock;
}		t_config;

void		better_usleep(int ms);
void		*start_routine(void *thread);
long long	timestamp(void);
void		format(t_philo *philo, char *str);
void		print_death(t_config *config, t_philo *philo);
int			ft_atoi(const char *str);
void		*start_death_check_threads(t_config *config);

#endif
