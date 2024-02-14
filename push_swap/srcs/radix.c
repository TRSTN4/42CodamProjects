/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 13:37:59 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 15:42:34 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_list *stack)
{
	t_list	*temp;
	t_list	*temp2;

	temp = stack;
	temp2 = temp->next;
	while (temp->next != NULL)
	{
		if (temp->index > temp2->index)
			return (0);
		temp = temp->next;
		temp2 = temp2->next;
	}
	return (1);
}

void	radix_sort(t_list **stack_a, t_list **stack_b)
{
	int	i;
	int	size;

	i = 0;
	while (!is_sorted(*stack_a))
	{
		size = ft_lstsize(*stack_a);
		while (size--)
		{
			if (((*stack_a)->index >> i) & 1)
				rotate(stack_a, "ra");
			else
				push(stack_a, stack_b, "pb");
		}
		while (*stack_b != NULL)
			push(stack_b, stack_a, "pa");
		i++;
	}
}
