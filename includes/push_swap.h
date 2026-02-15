/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:56:30 by Visual            #+#    #+#             */
/*   Updated: 2026/02/15 13:40:43 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

// Stack Structure

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

// Parsing & Validation

long		ft_atol(const char *str);
int			has_duplicates(t_stack *stack);
int			is_valid_int(char *str);
int			parse_args(char **argv, t_stack **a);

// Stack Data Structure

t_stack		*stack_new(int value);
void		stack_add_back(t_stack **stack, t_stack *new);
int			stack_size(t_stack *stack);
t_stack		*stack_last(t_stack *stack);
void		stack_clear(t_stack **stack);

// Stack Operations - Swap

void		sa(t_stack **a, int print);
void		sb(t_stack **b, int print);
void		ss(t_stack **a, t_stack **b, int print);

// Stack Operations - Push

void		pa(t_stack **a, t_stack **b, int print);
void		pb(t_stack **a, t_stack **b, int print);

// Stack Operations - Rotate

void		ra(t_stack **a, int print);
void		rb(t_stack **b, int print);
void		rr(t_stack **a, t_stack **b, int print);

// Stack Operations - Reverse Rotate

void		rra(t_stack **a, int print);
void		rrb(t_stack **b, int print);
void		rrr(t_stack **a, t_stack **b, int print);

// Algorithms

void		index_stack(t_stack **stack);
int			is_sorted(t_stack *stack);
void		radix_sort(t_stack **a, t_stack **b);
void		sort_five(t_stack **a, t_stack **b);
void		sort_three(t_stack **a);

#endif
