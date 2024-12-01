/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_transform2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:40:30 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/02 02:50:25 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void fill_new_str(char *old_str, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (old_str[i] != DQUOTE && old_str[i] != SQUOTE)
			new_str[j++] = old_str[i++];
		else
			i++;
	}
}

char	*remove_quotes(char *old_str)
{
    size_t	len;
    char	*new_str;

    len = ft_strlen(old_str);
    new_str = ft_calloc(len + 1, sizeof(char));
    if (!new_str)
        return (perror("malloc"), free(old_str), NULL);
    fill_new_str(old_str, new_str);
    free(old_str);
    return (new_str);
}

int	check_bracket_syntax(char *line, int bracket_level, int empty_brackets)
{
	if (bracket_level < 0)
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing opening parenthesis\e[0m", STDERR_FILENO);
		return (0);
	}
	else if (empty_brackets && line[0] == ')')
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Empty parenthesis\e[0m", STDERR_FILENO);
		return (0);
	}
	return (1);
}
