/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:28:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/18 22:11:07 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_cmd_redirection_branches(t_syntax_tree **redir_branches, char **redir_split_arr, char **new_envp)
{
	int		i;
	char	*filename;

	i = 0;
	if (!find_redirections(redir_split_arr[i]))
	{
		redir_branches[i]->type = COMMAND;
		redir_branches[i]->value = redir_split_arr[i];
		i++;
	}
	while (redir_split_arr[i])
	{
		if (ft_strncmp(redir_split_arr[i], "<<", 2) == 0)
			redir_branches[i]->type = DOUBLE_LEFT;
		else if (ft_strncmp(redir_split_arr[i], "<", 1) == 0)
			redir_branches[i]->type = SINGLE_LEFT;
		else if (ft_strncmp(redir_split_arr[i], ">>", 2) == 0)
			redir_branches[i]->type = DOUBLE_RIGHT;
		else
			redir_branches[i]->type = SINGLE_RIGHT;
		redir_branches[i]->value = redir_split_arr[i];
		redir_branches[i + 1]->type = T_FILE;
		filename = perform_expansions(redir_split_arr[i + 1], new_envp);
		if (!filename)
			return (0);
		redir_branches[i + 1]->value = revert_transform(filename);
		i += 2;
	}
	if (redir_branches[0]->type != COMMAND)
		return (1);
	return (create_cmd_name_args_branches(redir_branches[0], new_envp));
}

int	create_redirection_branches(t_syntax_tree *stree, char *pipe_split, char **new_envp)
{
	char	**redir_split_arr;
	int		i;

	stree->type = REDIRECTION;
	redir_split_arr = redirection_split(pipe_split);
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
	if (!create_cmd_redirection_branches(stree->branches, redir_split_arr, new_envp))
	{
		free_2d_malloc_array(&redir_split_arr);
		return (0);
	}
	free(redir_split_arr[stree->num_branches]);
	free(redir_split_arr);
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

int	create_pipe_branches(t_syntax_tree **stree, char *line, char **new_envp)
{
	char	**pipe_split;
	int		i;

	pipe_split = line_split(line, "|");
	if (!pipe_split)
	{
		printf("Malloc failed for pipe_split\n");
		return (0);
	}
	(*stree)->num_branches = count_split_elements(pipe_split);
	(*stree)->branches = ft_calloc((*stree)->num_branches, sizeof(t_syntax_tree *));
	if (!(*stree)->branches)
	{
		printf("Malloc failed for branches\n");
		return (0);
	}
	i = 0;
	while (i < (*stree)->num_branches)
	{
		(*stree)->branches[i] = ft_calloc(1, sizeof(t_syntax_tree));
		if (!(*stree)->branches[i])
		{
			printf("Malloc failed for branch\n");
			free_2d_malloc_array(&pipe_split);
			return (0);
		}
		if (!(create_redirection_branches((*stree)->branches[i], pipe_split[i], new_envp)))
			return (0);
		i++;
	}
	free_2d_malloc_array(&pipe_split);
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
	(*stree)->type = PIPE;
	if (!create_pipe_branches(stree, line, new_envp))
		return (0);
	return (1);
}
