/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   force_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 13:40:42 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 13:48:55 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_list **stack)
{
	int	first;
	int	second;

	first = (*stack)->index;
	second = (*stack)->next->index;
	if (first > second)
		swap(stack, "sa");
}

void	sort_three(t_list **stack)
{
	int	first;
	int	second;
	int	third;

	first = (*stack)->index;
	second = (*stack)->next->index;
	third = (*stack)->next->next->index;
	if (first > second && second > third)
	{
		swap(stack, "sa");
		reverse_rotate(stack, "rra");
	}
	else if (second > first && first > third && second > third)
		reverse_rotate(stack, "rra");
	else if (first > second && first < third && second < third)
		swap(stack, "sa");
	else if (first > third && second < third && first > second)
		rotate(stack, "ra");
	else if (first < third && second > third && first < second)
	{
		swap(stack, "sa");
		rotate(stack, "ra");
	}
}

t_list	*find_smallest_index(t_list *stack)
{
	t_list	*temp;
	t_list	*min_index_node;

	temp = stack;
	min_index_node = temp;
	while (temp != NULL)
	{
		if (temp->index < min_index_node->index)
			min_index_node = temp;
		temp = temp->next;
	}
	return (min_index_node);
}

int	get_node_position(t_list *stack, t_list *node)
{
	t_list	*temp;
	int		position;

	temp = stack;
	position = 0;
	while (temp != node && temp != NULL)
	{
		position++;
		temp = temp->next;
	}
	return (position);
}

void	sort_four_five(t_list **stack_a, t_list **stack_b, int len)
{
	t_list	*min_index_node;
	int		position;
	int		size_b;

	while (len > 0)
	{
		min_index_node = find_smallest_index(*stack_a);
		position = get_node_position(*stack_a, min_index_node);
		if (position <= ft_lstsize(*stack_a) / 2)
		{
			while ((*stack_a) != min_index_node)
				rotate(stack_a, "ra");
		}
		else
		{
			while ((*stack_a) != min_index_node)
				reverse_rotate(stack_a, "rra");
		}
		push(stack_a, stack_b, "pb");
		len--;
	}
	sort_three(stack_a);
	size_b = ft_lstsize(*stack_b);
	while (size_b-- > 0)
		push(stack_b, stack_a, "pa");
}
