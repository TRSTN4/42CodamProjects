/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 12:24:19 by trstn4        #+#    #+#                 */
/*   Updated: 2023/01/27 13:32:30 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// 
// ft_printf("\n%i\n", i);

static void	ft_receive_signal(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
	{
		i |= (1 << bit);
	}
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	ft_printf("PID = %d\n", getpid());
	signal(SIGUSR1, ft_receive_signal);
	signal(SIGUSR2, ft_receive_signal);
	while (1)
		pause ();
	return (0);
}
