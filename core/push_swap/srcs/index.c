/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:11:26 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 16:05:41 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*find_smallest_unindexed(t_list *stack, int *min_value)
{
	t_list	*current;
	t_list	*seeker;
	int		found;

	current = stack;
	seeker = NULL;
	found = 0;
	while (current)
	{
		if (current->index == -1 && *((int *)current->content) <= *min_value)
		{
			*min_value = *((int *)current->content);
			seeker = current;
			found = 1;
		}
		current = current->next;
	}
	if (found)
		return (seeker);
	return (NULL);
}

void	assign_indexes(t_list *stack)
{
	t_list	*seeker;
	int		index;
	int		min_value;

	index = 0;
	while (index < ft_lstsize(stack))
	{
		min_value = 2147483647;
		seeker = find_smallest_unindexed(stack, &min_value);
		if (seeker)
			seeker->index = index++;
	}
}
