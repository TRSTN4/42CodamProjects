/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlowcase.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 17:58:08 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/25 14:07:43 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		else
			i++;
	}
	return (str);
}

/*
#include <stdio.h>
int	main(void)
{
	char str[] = "LOWer CaSE Me";
	printf("Output: %s", ft_strlowcase(str));
}
*/
