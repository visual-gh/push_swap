/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:49:53 by Visual            #+#    #+#             */
/*   Updated: 2026/02/08 21:46:11 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*compare;
	int		i;

	current = *stack;
	while (current)
	{
		i = 0;
		compare = *stack;
		while (compare)
		{
			if (compare->value < current->value)
				i++;
			compare = compare->next;
		}
		current->index = i;
		current = current->next;
	}
}

static int	get_max_bits(int size)
{
	int	bits;

	bits = 0;
	while ((size - 1) >> bits)
		bits++;
	return (bits);
}

static void	sort_bit(t_stack **stack_a, t_stack **stack_b, int bit, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((((*stack_a)->index >> bit) & 1) == 0)
			pb(stack_a, stack_b, 1);
		else
			ra(stack_a, 1);
		i++;
	}
	while (*stack_b)
		pa(stack_a, stack_b, 1);
}

void	radix_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	max_bits;
	int	bit;

	index_stack(stack_a);
	size = stack_size(*stack_a);
	max_bits = get_max_bits(size);
	bit = 0;
	while (bit < max_bits)
	{
		sort_bit(stack_a, stack_b, bit, size);
		bit++;
	}
}
