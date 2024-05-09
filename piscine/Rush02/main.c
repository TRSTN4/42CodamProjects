/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hflohil- <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/28 14:06:45 by hflohil-      #+#    #+#                 */
/*   Updated: 2022/08/28 14:06:46 by hflohil-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

unsigned int	ft_strlen(char *str);

int main(int argc, char *argv[])
{
	char *str;

	if (argc == 2)
	{
		str = malloc(ft_strlen(argv[1])); //dynamically allocating memory for the string and its length, since a char is 1 byte, size_of is redundant (as 1 * size = size)
		//load numbers.dict
	}

	else
	{
		//load new dict (argv[1])
		str = malloc(ft_strlen(argv[2]));
	}
	return (0);
}
