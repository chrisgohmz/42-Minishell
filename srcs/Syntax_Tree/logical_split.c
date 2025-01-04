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

#include "../../includes/minishell.h"

static char	*alloc_word(char *restrict start, char *restrict end)
{
	char	*word;
	int		i;
	int		j;
	int		within_brackets;

	word = ft_calloc(end - start + 1, sizeof(char));
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
			start_bracket_word(&words, &in_word, &in_delimiter,
				&within_brackets);
		else if (*str == ')')
			within_brackets--;
		else if (!within_brackets && (*str == '&' || (*str == '|'
					&& *(str + 1) == '|')) && !in_delimiter)
			start_delimiter(&words, &in_word, &in_delimiter, &str);
		else if (!within_brackets && !in_word && !(*str == '&'
				|| (*str == '|' && *(str + 1) == '|')))
			end_delimiter(&words, &in_word, &in_delimiter);
		str++;
	}
	return (words);
}

static void	insert_words(char **split, char *restrict str, int words)
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
		set_end(&end, &within_brackets);
		split[index] = alloc_word(start, end);
		if (!split[index++])
			return (free_2d_arr((void ***)&split));
		start = end;
		if (!*start)
			break ;
		end += 2;
		split[index] = alloc_word(start, end);
		if (!split[index++])
			return (free_2d_arr((void ***)&split));
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
