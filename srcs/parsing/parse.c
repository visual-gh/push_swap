/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:33:18 by Visual            #+#    #+#             */
/*   Updated: 2026/02/09 12:24:40 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Add a number to the stack after validation

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

// Free split on error

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

// Parse arguments that are space-separated in a single string

static int	parse_string(t_stack **stack, char *arg)
{
	char	**split;
	int		i;

	split = ft_split(arg, ' ');
	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		if (add_number(stack, split[i]))
			return (free_split(split), 1);
		i++;
	}
	return (free_split(split), 0);
}

// Main parsing function

int	parse_args(char **argv, t_stack **a)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (1);
	while (argv[i])
	{
		if (ft_strchr(argv[i], ' '))
		{
			if (parse_string(a, argv[i]))
				return (1);
		}
		else
		{
			if (add_number(a, argv[i]))
				return (1);
		}
		i++;
	}
	if (has_duplicates(*a))
		return (1);
	return (0);
}
