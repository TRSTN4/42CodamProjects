/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iterative_power.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 22:30:10 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/30 16:22:50 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	pwr;

	pwr = nb;
	while (power > 1)
	{
		pwr *= nb;
		power--;
	}
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (pwr);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%i", ft_iterative_power(3, 4));
}
*/
