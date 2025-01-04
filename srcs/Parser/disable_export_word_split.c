/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disable_export_word_split.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:46:42 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 18:14:23 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	disable_value_word_splitting(char *str)
{
	int		i;
	bool	disable;

	i = 0;
	disable = false;
	while (str[i])
	{
		if (str[i] == '=')
			disable = true;
		else if (disable && str[i] == '$')
			str[i] = DQUOTE_DOLLAR;
		else if (disable && str[i] == '*')
			str[i] = ESC_WILDCARD;
		i++;
	}
}

void	modify_expansions_if_export(t_syntax_tree *stree)
{
	int	i;

	i = 0;
	while (i < stree->num_branches)
	{
		if (stree->branches[i]->type == WORD)
		{
			if (ft_strncmp("export", stree->branches[i]->value,
					sizeof("export")) == 0)
				break ;
			else
				return ;
		}
		i++;
	}
	while (++i < stree->num_branches)
	{
		if (stree->branches[i]->type == WORD)
			disable_value_word_splitting(stree->branches[i]->value);
	}
}
