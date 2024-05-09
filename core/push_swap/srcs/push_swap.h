/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/05/22 16:11:34 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		main(int argc, char **argv);
void	swap(t_list **stack, char *act);
void	swap_both(t_list **stack_a, t_list **stack_b);
void	push(t_list **source, t_list **target, char *act);
void	rotate(t_list **stack, char *act);
void	rotate_both(t_list **stack_a, t_list **stack_b);
void	reverse_rotate(t_list **stack, char *act);
void	reverse_rotate_both(t_list **stack_a, t_list **stack_b);
void	add_num_to_stack_a(t_list **stack, int num);
int		check_duplicates(t_list *stack);
int		is_integer(char *str);
void	ft_free(t_list *stack_a, t_list *stack_b, int rate);
void	assign_indexes(t_list *stack);
int		valid_size(char *str);
void	radix_sort(t_list **stack_a, t_list **stack_b);
void	sort_two(t_list **stack);
void	sort_three(t_list **stack);
void	sort_four_five(t_list **stack_a, t_list **stack_b, int len);

#endif
