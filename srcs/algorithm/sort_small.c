/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:03 by Visual            #+#    #+#             */
/*   Updated: 2026/02/08 17:09:41 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	sort_three(t_stack **stack_a)
{
	int	top;
	int	mid;
	int	bot;

	top = (*stack_a)->value;
	mid = (*stack_a)->next->value;
	bot = (*stack_a)->next->next->value;
	if (top > mid && top > bot)
		ra(stack_a, 1);
	else if (mid > top && mid > bot)
		rra(stack_a, 1);
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}

static int	min_index_pos(t_stack *stack)
{
	int	min;
	int	pos;
	int	i;

	min = stack->index;
	pos = 0;
	i = 0;
	while (stack)
	{
		if (stack->index < min)
		{
			min = stack->index;
			pos = i;
		}
		stack = stack->next;
		i++;
	}
	return (pos);
}

static void	push_min(t_stack **stack_a, t_stack **stack_b)
{
	int	pos;
	int	size;

	pos = min_index_pos(*stack_a);
	size = stack_size(*stack_a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(stack_a, 1);
	}
	else
	{
		while (pos++ < size)
			rra(stack_a, 1);
	}
	pb(stack_a, stack_b, 1);
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	index_stack(stack_a);
	while (stack_size(*stack_a) > 3)
		push_min(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
		pb(stack_a, stack_b, 1);
}
