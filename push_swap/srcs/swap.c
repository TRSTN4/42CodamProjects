/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 16:07:04 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 13:36:37 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_list **stack, char *act)
{
	t_list	*first;
	t_list	*second;

	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
	ft_printf("%s\n", act);
}

void	swap_both(t_list **stack_a, t_list **stack_b)
{
	swap(stack_a, NULL);
	swap(stack_b, NULL);
	ft_printf("ss\n");
}
