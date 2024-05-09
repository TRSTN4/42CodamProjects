/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_is_alpha.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 16:53:13 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/25 13:47:02 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] > 96 && str[i] < 123) || (str[i] > 64 && str[i] < 91))
			i++;
		else
			return (0);
	}
	return (1);
}

/*
#include <stdio.h>
int main()
{
	printf("Output: %d ", ft_str_is_alpha("asfFs"));
}
*/
