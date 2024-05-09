/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_params.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:33:47 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/29 18:01:12 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	len;

	len = 1;
	while (len < argc)
	{
		i = 0;
		while (argv[len][i] != '\0')
		{
			write(1, &argv[len][i], 1);
			i++;
		}
		write(1, "\n", 1);
		len++;
	}
	return (0);
}
