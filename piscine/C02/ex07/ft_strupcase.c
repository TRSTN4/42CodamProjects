/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strupcase.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 17:55:30 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/25 14:06:07 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		else
			i++;
	}
	return (str);
}

/*
#include <stdio.h>
int main(void)
{
  char str[] = "thIS is not UppErcased.";
  printf("Output: %s", ft_strupcase(str));
}
*/
