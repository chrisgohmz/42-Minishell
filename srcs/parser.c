/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:57 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/20 20:35:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_tree(t_syntax_tree *stree)
{
	int	branch;

	branch = 0;
	while (stree->branches && branch < stree->num_branches)
	{
		parse_tree(stree->branches[branch]);
		branch++;
		if (branch < stree->num_branches && stree->type != COMMAND && stree->type != REDIRECTION)
			printf("token type: %d, token value: %s\n", stree->type, stree->value);
	}
	if (stree->type != COMMAND && stree->type != REDIRECTION && stree->type != PIPE)
		printf("token type: %d, token value: %s\n", stree->type, stree->value);
}
