/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_transform2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:40:30 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/27 16:45:30 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_quotes(char *old_str)
{
    int     new_len;
    int     i;
    int     j;
    char    *new_str;

    new_len = 0;
    i = 0;
    while (old_str[i])
	{
        if (old_str[i] != '"' && old_str[i] != '\'')
            new_len++;
        i++;
	}
    new_str = ft_calloc(new_len + 1, sizeof(char));
    if (!new_str)
	{
        perror("malloc");
        return (free(old_str), NULL);
	}
    i = 0;
    j = 0;
    while (j < new_len)
	{
        if (old_str[i] != '"' && old_str[i] != '\'')
            new_str[j++] = old_str[i];
        i++;
	}
    free(old_str);
    return (new_str);
}

int	check_bracket_syntax(char *line, int bracket_level, int empty_brackets)
{
	if (bracket_level < 0)
	{
		printf("\e[1;91mSyntax Error: Missing opening parenthesis\n\e[0m");
		return (0);
	}
	else if (empty_brackets && line[0] == ')')
	{
		printf("\e[1;91mSyntax Error: Empty parenthesis\n\e[0m");
		return (0);
	}
	return (1);
}
