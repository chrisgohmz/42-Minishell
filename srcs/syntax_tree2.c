/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:41:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/18 18:38:51 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*allocate_expanded_str(char *str, char **new_envp, size_t *expanded_size)
{
	int		i;
	char	*expanded_str;

	*expanded_size = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' || str[i] == DQUOTE_DOLLAR) && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			*expanded_size += ft_strlen(find_env_value(new_envp, str + i));
			i++;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		else if (str[i] != '"' && str[i] != '\'')
		{
			(*expanded_size)++;
			i++;
		}
		else
			i++;
	}
	expanded_str = ft_calloc(*expanded_size + 1, sizeof(char));
	return (expanded_str);
}

char	*perform_expansions(char *str, char **new_envp)
{
	char	*expanded_str;
	size_t	expanded_size;

	expanded_str = allocate_expanded_str(str, new_envp, &expanded_size);
	if (!expanded_str)
	{
		printf("Malloc failed for expanded_str\n");
		return (NULL);
	}
	fill_expanded_str(str, expanded_str, new_envp, expanded_size);
	free(str);
	return (expanded_str);
}

int	find_redirections(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	create_cmd_name_args_branches(t_syntax_tree *cmd_branch, char **new_envp)
{
	char	**cmd_split;
	int		i;

	cmd_branch->value = perform_expansions(cmd_branch->value, new_envp);
	if (!cmd_branch->value)
		return (0);
	cmd_split = line_split(cmd_branch->value, " \t");
	if (!cmd_split)
	{
		printf("Malloc failed for cmd_split\n");
		return (0);
	}
	cmd_branch->num_branches = count_split_elements(cmd_split);
	if (!cmd_branch->num_branches)
	{
		free_2d_malloc_array(&cmd_split);
		cmd_branch->branches = NULL;
		return (1);
	}
	cmd_branch->branches = ft_calloc(cmd_branch->num_branches, sizeof(t_syntax_tree *));
	if (!cmd_branch->branches)
	{
		printf("Malloc failed for branches\n");
		free_2d_malloc_array(&cmd_split);
		return (0);
	}
	i = 0;
	while (i < cmd_branch->num_branches)
	{
		cmd_branch->branches[i] = ft_calloc(1, sizeof(t_syntax_tree));
		if (!cmd_branch->branches[i])
		{
			printf("Malloc failed for branch\n");
			free_2d_malloc_array(&cmd_split);
			return (0);
		}
		i++;
	}
	cmd_branch->branches[0]->type = CMD_NAME;
	cmd_branch->branches[0]->value = revert_transform(cmd_split[0]);
	i = 1;
	while (i < cmd_branch->num_branches)
	{
		cmd_branch->branches[i]->type = CMD_ARGUMENT;
		cmd_branch->branches[i]->value = revert_transform(cmd_split[i]);
		i++;
	}
	free(cmd_split[cmd_branch->num_branches]);
	free(cmd_split);
	return (1);
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
