/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:38:33 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/08/29 18:05:37 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	part_write(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(1, &str[i++], 1);
}

int	compare_args(char *arg1, char *arg2)
{
	int	i;

	i = 0;
	while (arg1[i] != '\0' || arg2[i] != '\0')
	{
		if (arg1[i] == arg2[i])
			i++;
		if (arg1[i] < arg2[i] || arg1[i] > arg2[i])
			return (arg1[i] - arg2[i]);
	}
	return (0);
}

void	swap_args(char **arg1, char **arg2)
{
	char	*stored;

	stored = *arg1;
	*arg1 = *arg2;
	*arg2 = stored;
}

int	main(int argc, char **argv)
{
	int	j;
	int	x;
	int	i;

	x = 1;
	while (x < argc - 1)
	{
		j = 1;
		while (j < argc - 1)
		{
			if (compare_args(argv[j], argv[j + 1]) > 0)
				swap_args(&argv[j], &argv[j + 1]);
			j++;
		}
		x++;
	}
	j = 1;
	while (j < argc)
	{
		part_write(argv[j]);
		write(1, "\n", 1);
		j++;
	}
	return (0);
}
