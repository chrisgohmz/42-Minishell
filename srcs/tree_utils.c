/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:24:58 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/04 20:54:41 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_syntax_tree	*allocate_new_node(t_token_type type, char *value,
	int num_branches)
{
	t_syntax_tree	*node;

	node = ft_calloc(1, sizeof(t_syntax_tree) + num_branches
			* sizeof(t_syntax_tree *));
	if (!node)
	{
		perror("malloc");
		return (NULL);
	}
	node->type = type;
	node->value = value;
	node->num_branches = num_branches;
	return (node);
}

int	count_split_elements(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	free_syntax_tree(t_syntax_tree *stree)
{
	int	i;

	if (!stree)
		return ;
	i = 0;
	while (i < stree->num_branches)
	{
		free_syntax_tree(stree->branches[i]);
		i++;
	}
	free(stree->value);
	free(stree);
}
