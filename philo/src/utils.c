/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <tvan-bee@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/08 12:17:13 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/22 14:24:33 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		str++;
	while ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	result *= sign;
	if (str[1] == '+' || str[1] == '-')
		result = 0;
	return (result);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	better_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while ((timestamp() - time) < ms)
		usleep(400);
}

void	format(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->config->lock));
	if (philo->config->stop == 0)
		printf("%lld %d %s", \
			timestamp() - philo->config->start_time, philo->id, str);
	pthread_mutex_unlock(&(philo->config->lock));
}

void	print_death(t_config *config, t_philo *philo)
{
	printf("%lld %d %s", timestamp() - config->start_time, \
		philo->id, "died\n");
	config->stop = 1;
	pthread_mutex_unlock(&config->lock);
}
