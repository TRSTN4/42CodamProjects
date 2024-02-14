/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 15:46:27 by trstn4        #+#    #+#                 */
/*   Updated: 2023/05/22 16:11:29 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free(t_list *stack_a, t_list *stack_b, int rate)
{
	ft_lstclear(&stack_a, free);
	ft_lstclear(&stack_b, free);
	exit(rate);
}

void	add_num_to_stack_a(t_list **stack, int num)
{
	int		*content;
	t_list	*new_node;

	content = malloc(sizeof(int));
	if (!content)
		exit(1);
	*content = num;
	new_node = ft_lstnew(content);
	new_node->index = -1;
	ft_lstadd_back(stack, new_node);
}

int	is_integer(char *str)
{
	if (*str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_duplicates(t_list *stack)
{
	t_list	*current;
	t_list	*runner;

	current = stack;
	while (current != NULL)
	{
		runner = current->next;
		while (runner != NULL)
		{
			if (*((int *)current->content) == *((int *)runner->content))
				return (1);
			runner = runner->next;
		}
		current = current->next;
	}
	return (0);
}

int	valid_size(char *str)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + (str[i] - '0');
		if (sign > 0 && num > 2147483647)
			return (0);
		if (sign < 0 && num > 2147483648)
			return (0);
		i++;
	}
	return (1);
}
