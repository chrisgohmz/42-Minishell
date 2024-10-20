/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:41:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/20 19:49:05 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
