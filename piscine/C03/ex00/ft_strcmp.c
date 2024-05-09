/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 12:42:36 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/28 19:53:10 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char part1[] = "gt f g";
	char part2[] = "g fg gj";
	printf("%i\n", ft_strcmp(part1, part2));
	printf("%i\n", strcmp(part1, part2));
}
*/
