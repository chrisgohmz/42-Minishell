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
		if ((*str == '&' || (*str == '|' && *(str + 1) == '|')) && !in_delimiter)
		{
			words++;
			in_word = 0;
			in_delimiter = 1;
		}
		else if (!in_word && !(*str == '&' || (*str == '|' && *(str + 1) == '|')))
		{
			words++;
			in_word = 1;
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

	index = 0;
	start = str;
	end = start;
	while (*end && index < words)
	{
		while (*end && *end != '&' && !(*end == '|' && *(end + 1) == '|'))
			end++;
		split[index] = alloc_word(start, end);
		if (!split[index])
		{
			free_2d_malloc_array(&split);
			return ;
		}
		index++;
		start = end;
		if (!*start)
			break ;
		end += 2;
		split[index] = alloc_word(start, end);
		if (!split[index])
		{
			free_2d_malloc_array(&split);
			return ;
		}
		index++;
		start = end;
	}
	split[index] = NULL;
}

char	**logical_split(char *str)
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
