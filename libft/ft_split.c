/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:43:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/06 04:33:01 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc_word(char *restrict start, char *restrict end)
{
	char	*word;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, start, end - start);
	word[end - start] = '\0';
	return (word);
}

static int	count_words(const char *restrict s, char c)
{
	int	words;
	int	in_word;

	words = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			words++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (words);
}

static int	insert_words(char **split, char *restrict s, char c, int words)
{
	int		index;
	char	*start;
	char	*end;

	index = 0;
	end = s - 1;
	while (index < words)
	{
		start = end + 1;
		while (*start == c)
			start++;
		end = ft_strchr(start, c);
		if (!end)
			end = ft_strchr(start, '\0');
		split[index] = alloc_word(start, end);
		if (!split[index])
		{
			free_2d_arr((void ***)&split);
			return (-1);
		}
		index++;
	}
	split[index] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	words = count_words(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	if (insert_words(split, (char *)s, c, words) == -1)
		split = NULL;
	return (split);
}
