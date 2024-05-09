/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iterative_factorial.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 22:22:09 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/30 15:52:20 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	unsigned int	factr;

	factr = 1;
	while (nb > 0)
	{
		factr *= nb;
		nb--;
	}
	if (nb < 0)
		return (0);
	return (factr);
}

/*
#include <stdio.h>
int main (void)
{
	printf("%i", ft_iterative_factorial(5));
}
*/
