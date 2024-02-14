/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 12:24:15 by trstn4        #+#    #+#                 */
/*   Updated: 2023/01/27 13:02:07 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_char(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

static int	ft_prepare(char *arg, char *message)
{
	int	pid;
	int	i;

	pid = ft_atoi(arg);
	i = 0;
	while (message[i] != '\0')
	{
		ft_send_char(pid, message[i]);
		i++;
	}
	ft_send_char(pid, '\n');
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Error\nInvalid amount of arguments parsed.\n");
		return (0);
	}
	return (ft_prepare(argv[1], argv[2]));
}
