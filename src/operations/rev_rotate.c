/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:22:41 by Visual            #+#    #+#             */
/*   Updated: 2026/02/09 02:24:43 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Shifts all elements down by one.
** The last element becomes the first one.
**
** Before: [1, 2, 3, 4]
** After:  [4, 1, 2, 3]
*/

static void	rev_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*prev;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = *stack;
	prev = NULL;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	last->next = *stack;
	prev->next = NULL;
	*stack = last;
}

void	rra(t_stack **a, int print)
{
	rev_rotate(a);
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack **b, int print)
{
	rev_rotate(b);
	if (print)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack **a, t_stack **b, int print)
{
	rev_rotate(a);
	rev_rotate(b);
	if (print)
		write(1, "rrr\n", 4);
}
