/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:43:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/14 22:17:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*alloc_word(char *start, char *end)
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

static int	count_words(char *str, char *charset)
{
	int	words;
	int	in_word;

	words = 0;
	in_word = 0;
	while (*str)
	{
		if (!ft_strchr(charset, *str) && !in_word)
		{
			in_word = 1;
			words++;
		}
		else if (ft_strchr(charset, *str))
			in_word = 0;
		str++;
	}
	return (words);
}

static void	insert_words(char **split, char *str, char *charset, int words)
{
	int		index;
	char	*start;
	char	*end;

	index = 0;
	end = str;
	while (*end && index < words)
	{
		start = end;
		while (ft_strchr(charset, *start) && *start)
			start++;
		end = start;
		while (!ft_strchr(charset, *end) && *end)
			end++;
		split[index] = alloc_word(start, end);
		if (!split[index])
			free_2d_malloc_array(&split);
		index++;
	}
	split[index] = NULL;
}

char	**line_split(char *str, char *charset)
{
	int		words;
	char	**split;

	words = count_words(str, charset);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	insert_words(split, str, charset, words);
	return (split);
}
