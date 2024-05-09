/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcalc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 18:19:01 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/28 22:17:59 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void get_strlen(char *nbr)
{
	char i;
	char *keys[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	i = 0;
	while (nbr[i])
		i++;

	if (i == 1)
	{
		int conv = nbr[0] - '0';
		printf("%s", keys[conv]);
	}
}

int main(void)
{
	char nbr[] = "9";
	get_strlen(nbr);
}
