/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:57 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/24 17:54:08 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_tree(t_syntax_tree *stree)
{
	int	branch;

	branch = 0;
	while (stree->branches && branch < stree->num_branches && stree->type == REDIRECTION)
	{
		if (stree->branches[branch]->type == DOUBLE_LEFT || stree->branches[branch]->type == HEREDOC_DELIMITER || stree->branches[branch]->type == HEREDOC_QUOTED_DELIMITER)
			parse_tree(stree->branches[branch]);
		branch++;
	}
	branch = 0;
	while (stree->branches && branch < stree->num_branches && stree->type == REDIRECTION)
	{
		if (stree->branches[branch]->type != DOUBLE_LEFT && stree->branches[branch]->type != HEREDOC_DELIMITER && stree->branches[branch]->type != HEREDOC_QUOTED_DELIMITER)
			parse_tree(stree->branches[branch]);
		branch++;
	}
	while (stree->branches && branch < stree->num_branches && stree->type != REDIRECTION)
	{
		parse_tree(stree->branches[branch]);
		branch++;
		if (branch < stree->num_branches && stree->type != REDIRECTION && stree->type != ROOT)
			printf("token type: %d, token value: %s\n", stree->type, stree->value);
	}
	if (stree->type != REDIRECTION && stree->type != ROOT && stree->type != PIPE)
		printf("token type: %d, token value: %s\n", stree->type, stree->value);
}
