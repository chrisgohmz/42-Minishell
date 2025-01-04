/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_branches.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:10:17 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 19:49:15 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	extend_branches(t_syntax_tree *stree, char **pipe_split,
	int num_branches)
{
	int	i;

	i = 0;
	while (i < num_branches)
	{
		stree->branches[i] = create_redirection_branches(stree->branches[i],
				pipe_split[i]);
		if (!stree->branches[i])
		{
			free_2d_arr((void ***)&pipe_split);
			free_syntax_tree(stree);
			return (false);
		}
		i++;
	}
	return (true);
}

t_syntax_tree	*create_pipe_branches(t_syntax_tree *stree,
	char *value)
{
	char	**pipe_split;
	int		num_branches;

	pipe_split = ft_split(value, '|');
	if (!pipe_split)
		return (NULL);
	num_branches = count_split_elements(pipe_split);
	stree = allocate_new_node(PIPE, value, num_branches);
	if (!stree)
	{
		free_2d_arr((void ***)&pipe_split);
		return (NULL);
	}
	if (!extend_branches(stree, pipe_split, num_branches))
		return (NULL);
	free(pipe_split);
	return (stree);
}
