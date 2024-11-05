/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:57 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/05 20:43:54 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_cmd(char *expanded_str)
{
	int		i;
	char	**split_arr;

	split_arr = ft_multi_split(expanded_str, " \t");
	free(expanded_str);
	if (!split_arr)
		return (0);
	i = 0;
	while (split_arr[i])
	{
		split_arr[i] = revert_transform(split_arr[i]);
		printf("WORD: %s\n", split_arr[i]);
		i++;
	}
	free_2d_malloc_array(&split_arr);
	return (1);
}

int	parse_tree(t_syntax_tree *stree, char **new_envp)
{
	int		branch;
	char	*expanded_str;

	branch = 0;
	while (stree->branches && branch < stree->num_branches && stree->type == REDIRECTION)
	{
		if (stree->branches[branch]->type == DOUBLE_LEFT || stree->branches[branch]->type == HEREDOC_DELIMITER || stree->branches[branch]->type == HEREDOC_QUOTED_DELIMITER)
		{
			if (!parse_tree(stree->branches[branch], new_envp))
				return (0);
		}
		branch++;
	}
	branch = 0;
	while (stree->branches && branch < stree->num_branches && stree->type == REDIRECTION)
	{
		if (stree->branches[branch]->type != DOUBLE_LEFT && stree->branches[branch]->type != HEREDOC_DELIMITER && stree->branches[branch]->type != HEREDOC_QUOTED_DELIMITER)
		{
			if (!parse_tree(stree->branches[branch], new_envp))
				return (0);
		}
		branch++;
	}
	while (stree->branches && branch < stree->num_branches && stree->type != REDIRECTION)
	{
		if (!parse_tree(stree->branches[branch], new_envp))
			return (0);
		branch++;
		if (branch < stree->num_branches && stree->type != REDIRECTION && stree->type != ROOT && stree->type != BRACKETS)
			printf("token type: %d, token value: %s\n", stree->type, stree->value);
	}
	if (stree->type == WORD)
	{
		expanded_str = perform_parameter_expansions(stree->value, new_envp);
		if (!expanded_str)
			return (0);
		expanded_str = perform_wildcard_expansions(expanded_str);
		if (!expanded_str)
			return (0);
		if (!get_cmd(expanded_str))
			return (0);
	}
	else if (stree->type != REDIRECTION && stree->type != ROOT && stree->type != PIPE && stree->type != BRACKETS)
		printf("token type: %d, token value: %s\n", stree->type, stree->value);
	return (1);
}
