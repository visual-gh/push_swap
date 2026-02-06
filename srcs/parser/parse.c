/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:33:18 by Visual            #+#    #+#             */
/*   Updated: 2026/02/06 12:57:14 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Add a number to the stack after validation
** Returns 0 on success, 1 on error
*/

static int	add_number(t_stack **stack, char *nbr_str)
{
	t_stack	*new;
	int		nbr;

	if (!is_valid_int(nbr_str))
		return (1);
	nbr = (int)ft_atol(nbr_str);
	new = stack_new(nbr);
	if (!new)
		return (1);
	stack_add_back(stack, new);
	return (0);
}

/*
** Parse arguments that are space-separated in a single string
** Example: "./push_swap "4 67 3 87 23""
*/

static int	parse_quoted_args(t_stack **stack, char *arg)
{
	char	**str;
	int		i;

	str = ft_split(arg, ' ');
	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (add_number(stack, str[i]))
			return (free(str), 1);
		i++;
	}
	return (free(str), 0);
}

/*
** Main parsing function
** Handles both:
** - Individual args: ./push_swap 4 67 3 87 23
** - Quoted args:     ./push_swap "4 67 3 87 23"
*/

int	parse_args(char **av, t_stack **stack_a)
{
	int	i;

	i = 1;
	if (!av[1])
		return (1);
	while (av[i])
	{
		if (ft_strchr(av[i], ' '))
		{
			if (parse_quoted_args(stack_a, av[i]))
				return (1);
		}
		else
		{
			if (add_number(stack_a, av[i]))
				return (1);
		}
		i++;
	}
	if (has_duplicates(*stack_a))
		return (1);
	return (0);
}
