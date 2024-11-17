/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:43:31 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/17 15:11:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*alloc_word(char *start, char *end)
{
	char	*word;
	int		i;
	int		j;
	int		within_brackets;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	within_brackets = 0;
	while (start + i < end)
	{
		if (start[i] == '(')
			within_brackets++;
		else if (start[i] == ')')
			within_brackets--;
		if (within_brackets == 1 && start[i] == '(')
			i++;
		else if (!within_brackets && start[i] == ')')
			i++;
		else
			word[j++] = start[i++];
	}
	word[j] = '\0';
	return (word);
}

static int	count_words(char *str)
{
	int	words;
	int	in_word;
	int	in_delimiter;
	int	within_brackets;

	words = 0;
	in_word = 0;
	in_delimiter = 0;
	within_brackets = 0;
	while (*str)
	{
		if (*str == '(')
		{
			if (!within_brackets && !in_word)
				words++;
			within_brackets++;
			in_word = 1;
			in_delimiter = 0;
		}
		else if (*str == ')')
			within_brackets--;
		else if (!within_brackets && (*str == '&' || (*str == '|' && *(str + 1) == '|')) && !in_delimiter)
		{
			words++;
			str++;
			in_word = 0;
			in_delimiter = 1;
		}
		else if (!within_brackets && !in_word && !(*str == '&' || (*str == '|' && *(str + 1) == '|')))
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
	int		within_brackets;
	char	*start;
	char	*end;

	index = 0;
	within_brackets = 0;
	start = str;
	end = start;
	while (*end && index < words)
	{
		while (*end && (within_brackets || (*end != '&' && !(*end == '|' && *(end + 1) == '|'))))
		{
			if (*end == '(')
				within_brackets++;
			else if (*end == ')')
				within_brackets--;
			end++;
		}
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
