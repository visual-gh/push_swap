/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:43:54 by Visual            #+#    #+#             */
/*   Updated: 2026/02/08 21:37:29 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		size;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	if (parse_args(argv, &a))
		error_exit(&a, &b);
	size = stack_size(a);
	if (!is_sorted(a))
	{
		if (size == 2)
			sa(&a, 1);
		else if (size == 3)
			sort_three(&a);
		else if (size == 5)
			sort_five(&a, &b);
		else
			radix_sort(&a, &b);
	}
	stack_clear(&a);
	return (0);
}
