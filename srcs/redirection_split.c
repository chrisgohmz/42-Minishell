/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:43:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/18 21:56:26 by cgoh             ###   ########.fr       */
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

static char	*alloc_word(char *start, char *end, int index)
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
	{
		if (index > 0 && ft_strchr(" \t", start[i]))
		{
			i++;
			continue;
		}
		word[j++] = start[i++];
	}
	word[j] = '\0';
	return (word);
}

static int	count_words(char *str)
{
	int	words;
	int	in_word;

	words = 0;
	in_word = 0;
	if (ft_strchr("<>", *str))
		words++;
	while (*str)
	{
		if (!ft_strchr("<>", *str) && !in_word)
		{
			in_word = 1;
			words++;
		}
		else if (ft_strchr("<>", *str) && in_word)
		{
			in_word = 0;
			words++;
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
	end = str;
	while (ft_strchr("<>", *end))
		end++;
	if (start != end)
	{
		split[index] = alloc_word(start, end, index);
		index++;
	}
	while (*end && index < words)
	{
		start = end;
		while (!ft_strchr("<>", *end) && *end)
			end++;
		split[index] = alloc_word(start, end, index);
		index++;
		start = end;
		if (!*start)
			break ;
		while (ft_strchr("<>", *end) && *end)
			end++;
		split[index] = alloc_word(start, end, index);
		if (!split[index])
			return (free_2d_malloc_array(&split));
		index++;
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
