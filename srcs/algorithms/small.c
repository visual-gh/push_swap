/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:57:03 by Visual            #+#    #+#             */
/*   Updated: 2026/02/09 04:02:10 by Visual           ###   ########.fr       */
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

void	sort_three(t_stack **a)
{
	int	top;
	int	mid;
	int	bot;

	top = (*a)->value;
	mid = (*a)->next->value;
	bot = (*a)->next->next->value;
	if (top > mid && top > bot)
		ra(a, 1);
	else if (mid > top && mid > bot)
		rra(a, 1);
	if ((*a)->value > (*a)->next->value)
		sa(a, 1);
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

static void	push_min(t_stack **a, t_stack **b)
{
	int	pos;
	int	size;

	pos = min_index_pos(*a);
	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a, 1);
	}
	else
	{
		while (pos++ < size)
			rra(a, 1);
	}
	pb(a, b, 1);
}

void	sort_five(t_stack **a, t_stack **b)
{
	index_stack(a);
	while (stack_size(*a) > 3)
		push_min(a, b);
	sort_three(a);
	while (*b)
		pa(a, b, 1);
}
