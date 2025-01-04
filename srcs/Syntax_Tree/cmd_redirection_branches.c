/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirection_branches.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:28:25 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 20:08:27 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	allocate_word_file_redirection_nodes2(char *value,
	t_syntax_tree **stree_branches, int i)
{
	if (i && (stree_branches[i - 1]->type == SINGLE_LEFT
			|| stree_branches[i - 1]->type == DOUBLE_RIGHT
			|| stree_branches[i - 1]->type == SINGLE_RIGHT))
		stree_branches[i] = allocate_new_node(T_FILE, value, 0);
	else
		stree_branches[i] = allocate_new_node(WORD, value, 0);
}

static void	allocate_word_file_redirection_nodes(char *value,
	bool *is_heredoc_delimiter, t_syntax_tree **stree_branches, int i)
{
	if (ft_strncmp(value, "<<", 2) == 0)
	{
		stree_branches[i] = allocate_new_node(DOUBLE_LEFT, value, 0);
		*is_heredoc_delimiter = true;
	}
	else if (ft_strncmp(value, "<", 1) == 0)
		stree_branches[i] = allocate_new_node(SINGLE_LEFT, value, 0);
	else if (ft_strncmp(value, ">>", 2) == 0)
		stree_branches[i] = allocate_new_node(DOUBLE_RIGHT, value, 0);
	else if (ft_strncmp(value, ">", 1) == 0)
		stree_branches[i] = allocate_new_node(SINGLE_RIGHT, value, 0);
	else if (*is_heredoc_delimiter && (ft_strchr(value, DQUOTE)
			|| ft_strchr(value, SQUOTE)))
	{
		stree_branches[i] = allocate_new_node(HEREDOC_QUOTED_DELIMITER,
				revert_transform(remove_quotes(value)), 0);
		*is_heredoc_delimiter = false;
	}
	else if (*is_heredoc_delimiter)
	{
		stree_branches[i] = allocate_new_node(HEREDOC_DELIMITER, value, 0);
		*is_heredoc_delimiter = false;
	}
	else
		allocate_word_file_redirection_nodes2(value, stree_branches, i);
}

int	create_word_file_redirection_branches(t_syntax_tree *stree,
	char **redir_split_arr)
{
	int		i;
	bool	is_heredoc_delimiter;

	i = 0;
	is_heredoc_delimiter = false;
	while (redir_split_arr[i])
	{
		allocate_word_file_redirection_nodes(redir_split_arr[i],
			&is_heredoc_delimiter, stree->branches, i);
		if (!stree->branches[i])
			return (0);
		i++;
	}
	return (1);
}
