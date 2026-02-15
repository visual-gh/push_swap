/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:49:53 by Visual            #+#    #+#             */
/*   Updated: 2026/02/09 19:27:22 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Assign sorted position indices to each element in the stack

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

// Calculate number of bits needed to represent stack size

static int	get_max_bits(int size)
{
	int	bits;

	bits = 0;
	while ((size - 1) >> bits)
		bits++;
	return (bits);
}

// Sort elements based on a specific bit position

static void	sort_bit(t_stack **a, t_stack **b, int bit, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((((*a)->index >> bit) & 1) == 0)
			pb(a, b, 1);
		else
			ra(a, 1);
		i++;
	}
	while (*b)
		pa(a, b, 1);
}

// Main radix sort algorithm sorting bit by bit

void	radix_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	max_bits;
	int	bit;

	index_stack(a);
	size = stack_size(*a);
	max_bits = get_max_bits(size);
	bit = 0;
	while (bit < max_bits)
	{
		sort_bit(a, b, bit, size);
		bit++;
	}
}
