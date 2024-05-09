/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 16:09:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 13:30:44 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_list **source, t_list **target, char *act)
{
	t_list	*node_to_move;

	node_to_move = *source;
	*source = (*source)->next;
	node_to_move->next = NULL;
	node_to_move->next = *target;
	*target = node_to_move;
	ft_printf("%s\n", act);
}
