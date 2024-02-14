/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <tvan-bee@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/08 12:17:22 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/22 11:50:01 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	fill_config(t_config *config, char **argv)
{
	config->number_of_philosophers = ft_atoi(argv[1]);
	config->philo = malloc(sizeof(t_philo) * config->number_of_philosophers);
	if (config->philo == NULL)
		return (1);
	config->stop = 0;
	config->philos_finished_eating = 0;
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->eat_goal = -1;
	if (argv[5])
		config->eat_goal = ft_atoi(argv[5]);
	config->start_time = timestamp();
	if (pthread_mutex_init(&config->lock, NULL) != 0)
		return (-1);
	return (0);
}

int	fill_philo(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		config->philo[i].id = i + 1;
		config->philo[i].times_eaten = 0;
		config->philo[i].last_time_eaten = timestamp();
		config->philo[i].config = config;
		config->philo[i].fork_r = NULL;
		if (pthread_mutex_init(&(config->philo[i].fork_l), NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (i == config->number_of_philosophers - 1)
			config->philo[i].fork_r = &config->philo[0].fork_l;
		else
			config->philo[i].fork_r = &config->philo[i + 1].fork_l;
		i++;
	}
	return (0);
}

int	start_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_create(&config->philo[i].thread, NULL, \
				&start_routine, &(config->philo[i])) != 0)
			return (-1);
		i++;
	}
	start_death_check_threads(config);
	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_join(config->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	arguments_are_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			rtn;
	int			i;

	if ((argc != 5 && argc != 6) || (argv[5] && ft_atoi(argv[5]) == 0))
		return (0);
	if (arguments_are_digits(argv))
		return (printf("Error\nArguments must be numerical digits.\n"), 0);
	rtn = fill_config(&config, argv);
	if (rtn == 1)
		return (0);
	if (rtn == -1)
		return (free(config.philo), 0);
	if (fill_philo(&config) != -1)
		start_threads(&config);
	i = 0;
	while (i < config.number_of_philosophers)
	{
		pthread_mutex_destroy(&config.philo[i].fork_l);
		i++;
	}
	pthread_mutex_destroy(&config.lock);
	free(config.philo);
	return (0);
}
