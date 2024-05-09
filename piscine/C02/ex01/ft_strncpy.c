/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 16:13:30 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/29 15:37:37 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int main(void) {
  char src[] = "Hello World!!!";
  char dest[25];

  printf("ft_strncpy: %s\n", ft_strncpy(dest, src, 25));
  printf("strncpy: %s", strncpy(dest, src, 25));
  return (0);
}
*/
