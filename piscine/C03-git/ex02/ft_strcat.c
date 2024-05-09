/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 14:47:57 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/28 19:54:08 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strcat(char *dest, char *src)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	if (!dest || !src)
		return (dest);
	while (dest[i1] != '\0')
		i1++;
	while (src[i2] != '\0')
	{
		dest[i1 + i2] = src[i2];
		i2++;
	}
	dest[i1 + i2] = '\0';
	return (dest);
}

/*
#include <string.h>
int main()
{
	char dest[100] = "I added this: ";
	char src[100] = "string!";

	printf("%s\n", ft_strcat(dest, src));
}
*/
