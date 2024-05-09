/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 22:49:17 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/30 16:49:08 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	float	equals;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	equals = 2;
	if (nb >= 2)
	{
		while (equals * equals <= nb)
		{
			if (equals * equals == nb)
				return (equals);
			equals++;
		}
	}
	return (0);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%d is %d\n", 0, ft_sqrt(0));
	printf("%d is %d\n", 1, ft_sqrt(1));
	printf("%d is %d\n", 2, ft_sqrt(2));
	printf("%d is %d\n", 3, ft_sqrt(3));
	printf("%d is %d\n", 4, ft_sqrt(4));
	printf("%d is %d\n", 9, ft_sqrt(9));
}
*/
