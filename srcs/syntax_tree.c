/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:28:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/02 01:29:22 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_cmd_redirection_branches(t_syntax_tree **redir_branches, char **redir_split_arr, t_ms_vars *ms_vars)
{
	int		i;

	i = 0;
	while (redir_split_arr[i])
	{
		if (ft_strncmp(redir_split_arr[i], "<<", 2) == 0)
			redir_branches[i]->type = DOUBLE_LEFT;
		else if (ft_strncmp(redir_split_arr[i], "<", 1) == 0)
			redir_branches[i]->type = SINGLE_LEFT;
		else if (ft_strncmp(redir_split_arr[i], ">>", 2) == 0)
			redir_branches[i]->type = DOUBLE_RIGHT;
		else if (ft_strncmp(redir_split_arr[i], ">", 1) == 0)
			redir_branches[i]->type = SINGLE_RIGHT;
		else if (i != 0 && redir_branches[i - 1]->type == DOUBLE_LEFT && (ft_strchr(redir_split_arr[i], '"') || ft_strchr(redir_split_arr[i], '\'')))
			redir_branches[i]->type = HEREDOC_QUOTED_DELIMITER;
		else if (i != 0 && redir_branches[i - 1]->type == DOUBLE_LEFT)
			redir_branches[i]->type = HEREDOC_DELIMITER;
		else if (i != 0 && (redir_branches[i - 1]->type == SINGLE_LEFT
		|| redir_branches[i - 1]->type == DOUBLE_RIGHT || redir_branches[i - 1]->type == SINGLE_RIGHT))
			redir_branches[i]->type = T_FILE;
		else
			redir_branches[i]->type = WORD;
		if (redir_branches[i]->type == HEREDOC_QUOTED_DELIMITER)
		{
			redir_branches[i]->value = remove_quotes(redir_split_arr[i]);
			if (!redir_branches[i]->value)
			{
				free_2d_malloc_array(&redir_split_arr);
				ms_vars->exit_value = EXIT_FAILURE;
				error_cleanup(ms_vars);
			}
		}
		else
			redir_branches[i]->value = redir_split_arr[i];
		i++;
	}
}

void	create_redirection_branches(t_syntax_tree *stree, char *pipe_split, t_ms_vars *ms_vars)
{
	char	**redir_split_arr;
	int		i;

	stree->type = REDIRECTION;
	redir_split_arr = redirection_split(pipe_split);
	if (!redir_split_arr)
		error_cleanup(ms_vars);
	stree->num_branches = count_split_elements(redir_split_arr);
	stree->branches = allocate_new_node(stree->num_branches, sizeof(t_syntax_tree *), ms_vars);
	i = 0;
	while (i < stree->num_branches)
	{
		stree->branches[i] = allocate_new_node(1, sizeof(t_syntax_tree), ms_vars);
		i++;
	}
	create_cmd_redirection_branches(stree->branches, redir_split_arr, ms_vars);
	free(redir_split_arr[stree->num_branches]);
	free(redir_split_arr);
}

void	create_pipe_branches(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	char	**pipe_split;
	int		i;

	pipe_split = ft_split(stree->value, '|');
	if (!pipe_split)
		error_cleanup(ms_vars);
	stree->num_branches = count_split_elements(pipe_split);
	stree->branches = allocate_new_node(stree->num_branches, sizeof(t_syntax_tree *), ms_vars);
	i = 0;
	while (i < stree->num_branches)
	{
		stree->branches[i] = allocate_new_node(1, sizeof(t_syntax_tree), ms_vars);
		create_redirection_branches(stree->branches[i], pipe_split[i], ms_vars);
		i++;
	}
	free_2d_malloc_array(&pipe_split);
}

void	create_logical_branches(t_syntax_tree **stree, char *line, t_ms_vars *ms_vars)
{
	char	**logical_split_arr;
	int		i;
	size_t	len;

	logical_split_arr = logical_split(line);
	if (!logical_split_arr)
		error_cleanup(ms_vars);
	(*stree)->num_branches = count_split_elements(logical_split_arr);
	(*stree)->branches = allocate_new_node((*stree)->num_branches, sizeof(t_syntax_tree *), ms_vars);
	i = 0;
	while (i < (*stree)->num_branches)
	{
		len = ft_strlen(logical_split_arr[i]);
		(*stree)->branches[i] = allocate_new_node(1, sizeof(t_syntax_tree), ms_vars);
		(*stree)->branches[i]->value = logical_split_arr[i];
		if (ft_strncmp(logical_split_arr[i], "&&", sizeof("&&")) == 0)
			(*stree)->branches[i]->type = AND;
		else if (ft_strncmp(logical_split_arr[i], "||", sizeof("||")) == 0)
			(*stree)->branches[i]->type = OR;
		else if (ft_strnstr(logical_split_arr[i], "&&", len)
			|| ft_strnstr(logical_split_arr[i], "||", len)
			|| ft_strchr(logical_split_arr[i], '('))
		{
			(*stree)->branches[i]->type = BRACKETS;
			create_logical_branches(&(*stree)->branches[i], logical_split_arr[i], ms_vars);
		}
		else
		{
			(*stree)->branches[i]->type = PIPE;
			create_pipe_branches((*stree)->branches[i], ms_vars);
		}
		i++;
	}
	free(logical_split_arr[i]);
	free(logical_split_arr);
}

void	create_syntax_tree(t_syntax_tree **stree, char *line, t_ms_vars *ms_vars)
{
	*stree = allocate_new_node(1, sizeof(t_syntax_tree), ms_vars);
	(*stree)->type = ROOT;
	create_logical_branches(stree, line, ms_vars);
}
