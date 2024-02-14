/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <tvan-bee@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/08 12:17:17 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/22 14:31:44 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sub_check(t_config *config)
{
	if (config->philos_finished_eating == \
		config->number_of_philosophers)
	{
		config->stop = 1;
		return (1);
	}
	return (0);
}

void	*start_death_check_threads(t_config *config)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_lock(&config->lock);
			if (sub_check(config) == 1)
			{
				pthread_mutex_unlock(&config->lock);
				return (NULL);
			}
			if ((timestamp() - config->philo[i].last_time_eaten) >= \
				config->time_to_die)
			{
				print_death(config, &config->philo[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&config->lock);
			usleep(25);
			i++;
		}
	}
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	format(philo, "has taken a fork\n");
	if (philo->config->number_of_philosophers == 1)
	{
		better_usleep(philo->config->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	format(philo, "has taken a fork\n");
}

void	eat_sleep_think(t_philo *philo)
{
	format(philo, "is eating\n");
	pthread_mutex_lock(&(philo->config->lock));
	philo->last_time_eaten = timestamp();
	philo->times_eaten++;
	pthread_mutex_unlock(&(philo->config->lock));
	better_usleep(philo->config->time_to_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	format(philo, "is sleeping\n");
	better_usleep(philo->config->time_to_sleep);
	format(philo, "is thinking\n");
}

void	*start_routine(void *thread)
{
	t_philo		*philo;

	philo = (t_philo *)thread;
	if (philo->id % 2 == 0)
		better_usleep(philo->config->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->config->lock);
		if (philo->config->stop == 1)
		{
			pthread_mutex_unlock(&philo->config->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->config->lock);
		take_fork(philo);
		eat_sleep_think(philo);
		pthread_mutex_lock(&philo->config->lock);
		if (philo->config->eat_goal != -1 && \
			philo->times_eaten == philo->config->eat_goal)
			philo->config->philos_finished_eating++;
		pthread_mutex_unlock(&philo->config->lock);
	}
	return (NULL);
}
