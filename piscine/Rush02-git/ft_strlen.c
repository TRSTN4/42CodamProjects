/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_size_of.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hflohil- <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 14:02:48 by hflohil-      #+#    #+#                 */
/*   Updated: 2022/08/28 14:02:50 by hflohil-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

unsigned int	ft_strlen(char *str)
{
	unsigned int i;
	unsigned int size;

	i = 0;
	size = 0;
	while (!(str[i] != '\0'))
	{
		i++;
		size++;
	}
	size = size + 1;
	return (size);
}

/*
int main(void)
{
	printf("%d\n", ft_size_of("hellohello"));
	return 0;
}
*/