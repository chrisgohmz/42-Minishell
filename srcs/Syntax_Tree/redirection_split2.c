/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:30:25 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 20:53:49 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_vars(t_redir_split *rd_split_vars)
{
	if (ft_strchr("<>", *rd_split_vars->start))
	{
		rd_split_vars->in_delimiter = 1;
		rd_split_vars->in_word = 0;
	}
	else
	{
		rd_split_vars->in_delimiter = 0;
		rd_split_vars->in_word = 1;
	}
}

static char	*alloc_word(char *restrict start, char *restrict end)
{
	char	*word;
	int		i;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

bool	alloc_words(t_redir_split *rd_split_vars, char **split)
{
	while (*rd_split_vars->end && rd_split_vars->index < rd_split_vars->words)
	{
		while (rd_split_vars->in_delimiter && ft_strchr("<>",
				*rd_split_vars->end) && *rd_split_vars->end)
			rd_split_vars->end++;
		while (rd_split_vars->in_word && !ft_strchr("<> \t",
				*rd_split_vars->end) && *rd_split_vars->end)
			rd_split_vars->end++;
		split[rd_split_vars->index] = alloc_word(rd_split_vars->start,
				rd_split_vars->end);
		if (!split[rd_split_vars->index++])
			return (free_2d_arr((void ***)&split), false);
		rd_split_vars->start = rd_split_vars->end;
		if (!*rd_split_vars->start)
			break ;
		while (*rd_split_vars->start == ' ' || *rd_split_vars->start == '\t')
			rd_split_vars->start++;
		rd_split_vars->end = rd_split_vars->start;
		update_vars(rd_split_vars);
	}
	return (true);
}
