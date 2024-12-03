/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:24:58 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/04 01:56:17 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*allocate_new_node(size_t nmemb, size_t size, t_ms_vars *ms_vars)
{
	t_syntax_tree	*node;

	node = ft_calloc(nmemb, size);
	if (!node)
	{
		perror("malloc");
		exit_cleanup(ms_vars);
	}
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
	free(stree->branches);
	free(stree);
}
