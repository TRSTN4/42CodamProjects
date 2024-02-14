/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 12:26:00 by trstn4        #+#    #+#                 */
/*   Updated: 2024/02/14 16:56:42 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_and_error(t_list **stack_a, t_list **stack_b, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!valid_size(argv[i]))
		{
			ft_printf("Error\n", argv[i]);
			ft_free(*stack_a, *stack_b, 1);
		}
		if (!is_integer(argv[i]))
		{
			ft_printf("Error\n", argv[i]);
			ft_free(*stack_a, *stack_b, 1);
		}
		add_num_to_stack_a(stack_a, ft_atoi(argv[i]));
		i++;
	}
	if (check_duplicates(*stack_a))
	{
		ft_printf("Error\n");
		ft_free(*stack_a, *stack_b, 1);
	}
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	add_and_error(&stack_a, &stack_b, argc, argv);
	assign_indexes(stack_a);
	if (argc <= 2)
		return (0);
	else if (argc == 3)
		sort_two(&stack_a);
	else if (argc == 4)
		sort_three(&stack_a);
	else if (argc == 5)
		sort_four_five(&stack_a, &stack_b, 1);
	else if (argc == 6)
		sort_four_five(&stack_a, &stack_b, 2);
	else
		radix_sort(&stack_a, &stack_b);
	ft_free(stack_a, stack_b, 0);
	return (0);
}
