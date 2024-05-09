/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_is_printable.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 17:53:24 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/31 15:58:48 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 32)
		{
			++i;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}


#include <stdio.h>
int main(void)
{
	printf("%d", ft_str_is_printable(" "));
}

