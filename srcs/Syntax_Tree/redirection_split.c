/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:43:31 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 20:53:43 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_vars(char *str, int *words, int *in_word,
	int *in_delimiter)
{
	if (ft_strchr("<>", *str) && !*in_delimiter)
	{
		(*words)++;
		*in_word = 0;
		*in_delimiter = 1;
	}
	else if (!*in_word && !ft_strchr("<> \t", *str))
	{
		(*words)++;
		*in_word = 1;
		*in_delimiter = 0;
	}
	else if (ft_strchr(" \t", *str))
	{
		*in_word = 0;
		*in_delimiter = 0;
	}
}

static int	count_words(char *restrict str)
{
	int	words;
	int	in_word;
	int	in_delimiter;

	words = 0;
	in_word = 0;
	in_delimiter = 0;
	while (*str)
	{
		update_vars(str, &words, &in_word, &in_delimiter);
		str++;
	}
	return (words);
}

static void	insert_words(char **split, char *str, int words)
{
	t_redir_split	rd_split_vars;

	rd_split_vars.index = 0;
	rd_split_vars.start = str;
	rd_split_vars.in_word = 0;
	rd_split_vars.in_delimiter = 0;
	rd_split_vars.words = words;
	while (*rd_split_vars.start == ' ' || *rd_split_vars.start == '\t')
		rd_split_vars.start++;
	rd_split_vars.end = rd_split_vars.start;
	if (ft_strchr("<>", *rd_split_vars.start))
		rd_split_vars.in_delimiter = 1;
	else
		rd_split_vars.in_word = 1;
	if (alloc_words(&rd_split_vars, split))
		split[rd_split_vars.index] = NULL;
}

char	**redirection_split(char *str)
{
	int		words;
	char	**split;

	words = count_words(str);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	insert_words(split, str, words);
	return (split);
}
