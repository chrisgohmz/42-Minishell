/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_split2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:21:22 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 19:48:09 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_end(char **end, int *within_brackets)
{
	while (**end && (*within_brackets || (**end != '&' && !(**end == '|'
					&& *(*end + 1) == '|'))))
	{
		if (**end == '(')
			(*within_brackets)++;
		else if (**end == ')')
			(*within_brackets)--;
		(*end)++;
	}
}

void	end_delimiter(int *words, int *in_word, int *in_delimiter)
{
	(*words)++;
	*in_word = 1;
	*in_delimiter = 0;
}

void	start_delimiter(int *words, int *in_word, int *in_delimiter,
	char **str)
{
	(*words)++;
	(*str)++;
	*in_word = 0;
	*in_delimiter = 1;
}

void	start_bracket_word(int *words, int *in_word, int *in_delimiter,
	int *within_brackets)
{
	if (!*within_brackets && !*in_word)
		(*words)++;
	(*within_brackets)++;
	*in_word = 1;
	*in_delimiter = 0;
}
