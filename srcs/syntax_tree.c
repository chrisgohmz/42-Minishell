/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:28:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/21 20:40:05 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_cmd_redirection_branches(t_syntax_tree **redir_branches, char **redir_split_arr)
{
	int		i;
	int		cmd_name_found;

	i = 0;
	cmd_name_found = 0;
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
		else if (i != 0 && redir_branches[i - 1]->type == DOUBLE_LEFT && ft_strchr("'\"", redir_split_arr[i][0]))
			redir_branches[i]->type = HEREDOC_QUOTED_DELIMITER;
		else if (i != 0 && redir_branches[i - 1]->type == DOUBLE_LEFT)
			redir_branches[i]->type = HEREDOC_DELIMITER;
		else if (i != 0 && (redir_branches[i - 1]->type == SINGLE_LEFT
		|| redir_branches[i - 1]->type == DOUBLE_RIGHT || redir_branches[i - 1]->type == SINGLE_RIGHT))
			redir_branches[i]->type = T_FILE;
		else if (!cmd_name_found)
		{
			cmd_name_found = 1;
			redir_branches[i]->type = CMD_NAME;
		}
		else
			redir_branches[i]->type = CMD_ARGUMENT;
		if (redir_branches[i]->type == HEREDOC_QUOTED_DELIMITER)
			redir_split_arr[i] = remove_quotes(redir_split_arr[i]);
		if (!redir_split_arr[i])
			return (0);
		redir_branches[i]->value = revert_transform(redir_split_arr[i]);
		i++;
	}
	return (1);
}

int	create_redirection_branches(t_syntax_tree *stree, char *pipe_split, char **new_envp)
{
	char	**redir_split_arr;
	char	*expanded_str;
	int		i;

	stree->type = REDIRECTION;
	expanded_str = perform_expansions(pipe_split, new_envp);
	if (!expanded_str)
		return (0);
	redir_split_arr = redirection_split(expanded_str);
	if (!redir_split_arr)
	{
		printf("Malloc failed for redirection_split\n");
		return (0);
	}
	stree->num_branches = count_split_elements(redir_split_arr);
	stree->branches = ft_calloc(stree->num_branches, sizeof(t_syntax_tree *));
	if (!stree->branches)
	{
		printf("Malloc failed for branches\n");
		return (0);
	}
	i = 0;
	while (i < stree->num_branches)
	{
		stree->branches[i] = ft_calloc(1, sizeof(t_syntax_tree));
		if (!stree->branches[i])
		{
			printf("Malloc failed for branches\n");
			free_2d_malloc_array(&redir_split_arr);
			return (0);
		}
		i++;
	}
	if (!create_cmd_redirection_branches(stree->branches, redir_split_arr))
	{
		free_2d_malloc_array(&redir_split_arr);
		return (0);
	}
	free(redir_split_arr[stree->num_branches]);
	free(redir_split_arr);
	free(expanded_str);
	return (1);
}

int	count_split_elements(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	create_pipe_branches(t_syntax_tree *stree, char **new_envp)
{
	char	**pipe_split;
	int		i;

	pipe_split = ft_split(stree->value, '|');
	if (!pipe_split)
		return (0);
	stree->num_branches = count_split_elements(pipe_split);
	stree->branches = ft_calloc(stree->num_branches, sizeof(t_syntax_tree *));
	if (!stree->branches)
		return (free_2d_malloc_array(&pipe_split), 0);
	i = 0;
	while (i < stree->num_branches)
	{
		stree->branches[i] = ft_calloc(1, sizeof(t_syntax_tree));
		if (!stree->branches[i])
		{
			free_2d_malloc_array(&pipe_split);
			return (0);
		}
		if (!(create_redirection_branches(stree->branches[i], pipe_split[i], new_envp)))
			return (0);
		i++;
	}
	free_2d_malloc_array(&pipe_split);
	return (1);
}

int	create_logical_branches(t_syntax_tree **stree, char *line, char **new_envp)
{
	char	**logical_split_arr;
	int		i;

	logical_split_arr = logical_split(line);
	if (!logical_split_arr)
		return (0);
	(*stree)->num_branches = count_split_elements(logical_split_arr);
	(*stree)->branches = ft_calloc((*stree)->num_branches, sizeof(t_syntax_tree *));
	if (!(*stree)->branches)
		return (free_2d_malloc_array(&logical_split_arr), 0);
	i = 0;
	while (i < (*stree)->num_branches)
	{
		(*stree)->branches[i] = ft_calloc(1, sizeof(t_syntax_tree));
		if (!(*stree)->branches[i])
		{
			free_2d_malloc_array(&logical_split_arr);
			return (0);
		}
		(*stree)->branches[i]->value = logical_split_arr[i];
		if (ft_strncmp(logical_split_arr[i], "&&", 2) == 0)
			(*stree)->branches[i]->type = AND;
		else if (ft_strncmp(logical_split_arr[i], "||", 2) == 0)
			(*stree)->branches[i]->type = OR;
		else
		{
			(*stree)->branches[i]->type = LIST;
			if (!create_pipe_branches((*stree)->branches[i], new_envp))
				return (0);
		}
		i++;
	}
	free(logical_split_arr[i]);
	free(logical_split_arr);
	return (1);
}

int	create_syntax_tree(t_syntax_tree **stree, char *line, char **new_envp)
{
	*stree = ft_calloc(1, sizeof(t_syntax_tree));
	if (!*stree)
	{
		printf("Malloc failed for stree\n");
		return (0);
	}
	(*stree)->type = ROOT;
	if (!create_logical_branches(stree, line, new_envp))
		return (0);
	return (1);
}
