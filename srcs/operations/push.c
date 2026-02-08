/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:13:08 by Visual            #+#    #+#             */
/*   Updated: 2026/02/08 16:37:39 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Takes the first element from src and puts it on top of dst.
** Does nothing if src is empty.
**
** Before: src=[1, 2, 3]  dst=[4, 5]
** After:  src=[2, 3]     dst=[1, 4, 5]
*/

static void	push(t_stack **dst, t_stack **src)
{
	t_stack	*tmp;

	if (!src || !*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dst;
	*dst = tmp;
}

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	push(stack_a, stack_b);
	if (print)
		write(1, "pa\n", 3);
}

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
	push(stack_b, stack_a);
	if (print)
		write(1, "pb\n", 3);
}
