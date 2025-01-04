/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_branches.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:58:36 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 19:15:14 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	assign_nodes_and_extend_branches(t_syntax_tree *stree,
	char **logical_split_arr, int num_branches)
{
	int		i;
	size_t	len;
	char	*value;

	i = -1;
	while (++i < num_branches)
	{
		value = logical_split_arr[i];
		len = ft_strlen(value);
		if (ft_strncmp(value, "&&", sizeof("&&")) == 0)
			stree->branches[i] = allocate_new_node(AND, value, 0);
		else if (ft_strncmp(value, "||", sizeof("||")) == 0)
			stree->branches[i] = allocate_new_node(OR, value, 0);
		else if (ft_strnstr(value, "&&", len) || ft_strnstr(value, "||", len)
			|| ft_strchr(value, '('))
			stree->branches[i] = create_logical_branches(stree->branches[i],
					value);
		else
			stree->branches[i] = create_pipe_branches(stree->branches[i],
					value);
		if (!stree->branches[i])
			return (free(logical_split_arr), free_syntax_tree(stree), false);
	}
	return (true);
}

t_syntax_tree	*create_logical_branches(t_syntax_tree *stree, char *value)
{
	char	**logical_split_arr;
	int		num_branches;

	logical_split_arr = logical_split(value);
	if (!logical_split_arr)
		return (NULL);
	num_branches = count_split_elements(logical_split_arr);
	stree = allocate_new_node(BRACKETS, value, num_branches);
	if (!stree)
	{
		free_2d_arr((void ***)&logical_split_arr);
		return (NULL);
	}
	if (!assign_nodes_and_extend_branches(stree, logical_split_arr,
			num_branches))
		return (NULL);
	free(logical_split_arr);
	return (stree);
}
