/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 14:03:48 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/28 19:54:23 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i1;
	unsigned int	i2;

	i1 = 0;
	i2 = 0;
	if (!dest || !src)
		return (dest);
	while (dest[i1])
		i1++;
	while (src[i2] && i2 < nb)
	{
		dest[i1 + i2] = src[i2];
		i2++;
	}
	dest[i1 + i2] = '\0';
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char src[50] = "012345";
	char dest[50]= "This is my Test func:";
	printf("%s", ft_strncat(dest, src, 555));
}
*/
