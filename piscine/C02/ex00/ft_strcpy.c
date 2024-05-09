/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 12:56:36 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/24 18:52:08 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char src[] = "Copy Me!";
	char dest[50];

	printf("ft_strcpy: %s\n", ft_strcpy(dest, src));
	printf("strcpy: %s", strcpy(dest, src));
}
*/
