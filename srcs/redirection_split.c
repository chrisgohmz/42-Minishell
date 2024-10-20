/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:43:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/20 20:29:08 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_malloc_array(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

static char	*alloc_word(char *start, char *end)
{
	char	*word;
	int		i;
	int		j;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (start + i < end)
		word[j++] = start[i++];
	word[j] = '\0';
	return (word);
}

static int	count_words(char *str)
{
	int	words;
	int	in_word;
	int	in_delimiter;

	words = 0;
	in_word = 0;
	in_delimiter = 0;
	while (*str)
	{
		if (ft_strchr("<>", *str) && !in_delimiter)
		{
			words++;
			in_word = 0;
			in_delimiter = 1;
		}
		else if (!in_word && !ft_strchr("<> \t", *str))
		{
			words++;
			in_word = 1;
			in_delimiter = 0;
		}
		else if (ft_strchr(" \t", *str))
		{
			in_word = 0;
			in_delimiter = 0;
		}
		str++;
	}
	return (words);
}

static void	insert_words(char **split, char *str, int words)
{
	int		index;
	char	*start;
	char	*end;
	int		in_word;
	int		in_delimiter;

	index = 0;
	start = str;
	in_word = 0;
	in_delimiter = 0;
	while (*start == ' ' || *start == '\t')
		start++;
	end = start;
	if (ft_strchr("<>", *start))
		in_delimiter = 1;
	else
		in_word = 1;
	while (*end && index < words)
	{
		while (in_delimiter && ft_strchr("<>", *end) && *end)
			end++;
		while (in_word && !ft_strchr("<> \t", *end) && *end)
			end++;
		split[index] = alloc_word(start, end);
		index++;
		start = end;
		if (!*start)
			break ;
		while (*start == ' ' || *start == '\t')
			start++;
		end = start;
		if (ft_strchr("<>", *start))
		{
			in_delimiter = 1;
			in_word = 0;
		}
		else
		{
			in_delimiter = 0;
			in_word = 1;
		}
	}
	split[index] = NULL;
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
