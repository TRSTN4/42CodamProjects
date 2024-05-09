/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_comb.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:22:38 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/13 19:00:41 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	write_output(char c1, char c2, char c3)
{
	write(1, &c1, 1);
	write(1, &c2, 1);
	write(1, &c3, 1);
	write(1, ", ", 2);
}

void	ft_print_comb(void)
{
	char	c1;
	char	c2;
	char	c3;

	c1 = '0';
	c2 = '0';
	c3 = '0';
	while (c1 <= '9')
	{
		while (c2 <= '9')
		{
			while (c3 <= '9')
			{
				if (c3 > c2 && c2 > c1)
				{
					write_output(c1, c2, c3);
				}
				c3++;
			}
			c2++;
			c3 = '0';
		}
		c1++;
		c2 = '0';
	}
}
