/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_branches.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:49:44 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 20:50:23 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_syntax_tree	*create_redirection_branches(t_syntax_tree *stree,
	char *value)
{
	char	**redir_split_arr;
	int		num_branches;

	redir_split_arr = redirection_split(value);
	if (!redir_split_arr)
		return (NULL);
	num_branches = count_split_elements(redir_split_arr);
	stree = allocate_new_node(REDIRECTION, value, num_branches);
	if (!stree)
	{
		free_2d_arr((void ***)&redir_split_arr);
		return (NULL);
	}
	if (!create_word_file_redirection_branches(stree, redir_split_arr))
	{
		free(stree);
		free_2d_arr((void ***)&redir_split_arr);
		return (NULL);
	}
	free(redir_split_arr);
	return (stree);
}
