/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 14:40:54 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/28 19:53:40 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && n)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (s1[i] - s2[i]);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str1[] = "ak2ash";
	char str2[] = "aka3s";
	printf("%i\n", ft_strncmp(str1, str2, 4));
	printf("%i\n", strncmp(str1, str2, 4));
}
*/
