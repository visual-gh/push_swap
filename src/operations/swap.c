/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:03:10 by Visual            #+#    #+#             */
/*   Updated: 2026/02/09 02:24:50 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Swaps the first two elements at the top of the stack.
** Does nothing if there is only one or no elements.
**
** Before: [1, 2, 3, 4]
** After:  [2, 1, 3, 4]
*/

static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_stack **a, int print)
{
	swap(a);
	if (print)
		write(1, "sa\n", 3);
}

void	sb(t_stack **b, int print)
{
	swap(b);
	if (print)
		write(1, "sb\n", 3);
}

void	ss(t_stack **a, t_stack **b, int print)
{
	swap(a);
	swap(b);
	if (print)
		write(1, "ss\n", 3);
}
