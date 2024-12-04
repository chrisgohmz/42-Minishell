/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:28:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/04 20:52:40 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_cmd_redirection_branches(t_syntax_tree *stree,
	char **redir_split_arr)
{
	int		i;
	bool	is_heredoc_delimiter;

	i = 0;
	is_heredoc_delimiter = false;
	while (redir_split_arr[i])
	{
		if (ft_strncmp(redir_split_arr[i], "<<", 2) == 0)
		{
			stree->branches[i] = allocate_new_node(DOUBLE_LEFT,
					redir_split_arr[i], 0);
			is_heredoc_delimiter = true;
		}
		else if (ft_strncmp(redir_split_arr[i], "<", 1) == 0)
			stree->branches[i] = allocate_new_node(SINGLE_LEFT,
					redir_split_arr[i], 0);
		else if (ft_strncmp(redir_split_arr[i], ">>", 2) == 0)
			stree->branches[i] = allocate_new_node(DOUBLE_RIGHT,
					redir_split_arr[i], 0);
		else if (ft_strncmp(redir_split_arr[i], ">", 1) == 0)
			stree->branches[i] = allocate_new_node(SINGLE_RIGHT,
					redir_split_arr[i], 0);
		else if (is_heredoc_delimiter && (ft_strchr(redir_split_arr[i], '"')
				|| ft_strchr(redir_split_arr[i], '\'')))
		{
			stree->branches[i] = allocate_new_node(HEREDOC_QUOTED_DELIMITER,
					remove_quotes(redir_split_arr[i]), 0);
			is_heredoc_delimiter = false;
		}
		else if (is_heredoc_delimiter)
		{
			stree->branches[i] = allocate_new_node(HEREDOC_DELIMITER,
					redir_split_arr[i], 0);
			is_heredoc_delimiter = false;
		}
		else if (i && (stree->branches[i - 1]->type == SINGLE_LEFT
				|| stree->branches[i - 1]->type == DOUBLE_RIGHT
				|| stree->branches[i - 1]->type == SINGLE_RIGHT))
			stree->branches[i] = allocate_new_node(T_FILE,
					redir_split_arr[i], 0);
		else
			stree->branches[i] = allocate_new_node(WORD,
					redir_split_arr[i], 0);
		i++;
	}
	return (1);
}

t_syntax_tree	*create_redirection_branches(t_syntax_tree *stree, char *value)
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
		free_2d_malloc_array(&redir_split_arr);
		return (NULL);
	}
	create_cmd_redirection_branches(stree, redir_split_arr);
	free(redir_split_arr);
	return (stree);
}

t_syntax_tree	*create_pipe_branches(t_syntax_tree *stree, char *value)
{
	char	**pipe_split;
	int		i;
	int		num_branches;

	pipe_split = ft_split(value, '|');
	if (!pipe_split)
		return (NULL);
	num_branches = count_split_elements(pipe_split);
	stree = allocate_new_node(PIPE, value, num_branches);
	if (!stree)
	{
		free_2d_malloc_array(&pipe_split);
		return (NULL);
	}
	i = 0;
	while (i < num_branches)
	{
		stree->branches[i] = create_redirection_branches(stree->branches[i],
				pipe_split[i]);
		i++;
	}
	free(pipe_split);
	return (stree);
}

t_syntax_tree	*create_logical_branches(t_syntax_tree *stree, char *value,
	t_ms_vars *ms_vars)
{
	char	**logical_split_arr;
	int		i;
	size_t	len;
	int		num_branches;

	logical_split_arr = logical_split(value);
	if (!logical_split_arr)
		exit_cleanup(ms_vars);
	num_branches = count_split_elements(logical_split_arr);
	stree = allocate_new_node(BRACKETS, value, num_branches);
	if (!stree)
	{
		free_2d_malloc_array(&logical_split_arr);
		return (NULL);
	}
	i = 0;
	while (i < num_branches)
	{
		len = ft_strlen(logical_split_arr[i]);
		if (ft_strncmp(logical_split_arr[i], "&&", sizeof("&&")) == 0)
			stree->branches[i] = allocate_new_node(AND,
					logical_split_arr[i], 0);
		else if (ft_strncmp(logical_split_arr[i], "||", sizeof("||")) == 0)
			stree->branches[i] = allocate_new_node(OR,
					logical_split_arr[i], 0);
		else if (ft_strnstr(logical_split_arr[i], "&&", len)
			|| ft_strnstr(logical_split_arr[i], "||", len)
			|| ft_strchr(logical_split_arr[i], '('))
			stree->branches[i] = create_logical_branches(stree->\
			branches[i], logical_split_arr[i], ms_vars);
		else
			stree->branches[i] = create_pipe_branches(stree->\
			branches[i], logical_split_arr[i]);
		i++;
	}
	free(logical_split_arr);
	return (stree);
}

void	create_syntax_tree(t_syntax_tree **stree, char *line, t_ms_vars *ms_vars)
{
	char	**logical_split_arr;
	int		num_branches;
	int		i;
	size_t	len;

	logical_split_arr = logical_split(line);
	if (!logical_split_arr)
		exit_cleanup(ms_vars);
	num_branches = count_split_elements(logical_split_arr);
	*stree = allocate_new_node(ROOT, NULL, num_branches);
	if (!*stree)
	{
		free_2d_malloc_array(&logical_split_arr);
		exit_cleanup(ms_vars);
	}
	i = 0;
	while (i < num_branches)
	{
		len = ft_strlen(logical_split_arr[i]);
		if (ft_strncmp(logical_split_arr[i], "&&", sizeof("&&")) == 0)
			(*stree)->branches[i] = allocate_new_node(AND,
					logical_split_arr[i], 0);
		else if (ft_strncmp(logical_split_arr[i], "||", sizeof("||")) == 0)
			(*stree)->branches[i] = allocate_new_node(OR,
					logical_split_arr[i], 0);
		else if (ft_strnstr(logical_split_arr[i], "&&", len)
			|| ft_strnstr(logical_split_arr[i], "||", len)
			|| ft_strchr(logical_split_arr[i], '('))
			(*stree)->branches[i] = create_logical_branches((*stree)->\
			branches[i], logical_split_arr[i], ms_vars);
		else
			(*stree)->branches[i] = create_pipe_branches((*stree)->\
			branches[i], logical_split_arr[i]);
		i++;
	}
	free(logical_split_arr);
}
