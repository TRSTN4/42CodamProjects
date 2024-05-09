/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 16:07:11 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 13:33:25 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_list **stack, char *act)
{
	t_list	*first;

	first = *stack;
	*stack = first->next;
	first->next = NULL;
	ft_lstadd_back(stack, first);
	ft_printf("%s\n", act);
}

void	rotate_both(t_list **stack_a, t_list **stack_b)
{
	rotate(stack_a, NULL);
	rotate(stack_b, NULL);
	ft_printf("rr\n");
}

void	reverse_rotate(t_list **stack, char *act)
{
	t_list	*last;
	t_list	*previous;

	last = ft_lstlast(*stack);
	previous = *stack;
	while (previous->next != last)
		previous = previous->next;
	previous->next = NULL;
	last->next = *stack;
	*stack = last;
	ft_printf("%s\n", act);
}

void	reverse_rotate_both(t_list **stack_a, t_list **stack_b)
{
	reverse_rotate(stack_a, NULL);
	reverse_rotate(stack_b, NULL);
	ft_printf("rrr\n");
}
