/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_recursive_factorial.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 22:25:51 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/30 17:36:54 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	int	factr;

	factr = 1;
	if (nb > 0)
	{
		factr *= nb * ft_recursive_factorial(nb - 1);
		nb--;
	}
	if (nb < 0)
		return (0);
	return (factr);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%i", ft_recursive_factorial(5));
}
*/
