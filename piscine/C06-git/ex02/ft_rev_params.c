/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rev_params.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:36:28 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/29 15:17:26 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	len;
	int	i;

	len = argc - 1;
	while (len > 0)
	{
		i = 0;
		while (argv[len][i] != '\0' && argc)
		{
			write(1, &argv[len][i], 1);
			i++;
		}
		write(1, "\n", 1);
		len--;
	}
	return (0);
}
