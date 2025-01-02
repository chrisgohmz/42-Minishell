/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:47:05 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/02 20:43:15 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_closing_syntax(t_syntax_vars *svars)
{
	if (svars->within_squotes || svars->within_dquotes)
		return (ft_putendl_fd("\e[1;91mSyntax Error: unclosed quotes\e[0m",
				STDERR_FILENO), 1);
	else if (svars->searching_first_word)
		return (ft_putendl_fd("\e[1;91mSyntax Error: Missing command after |,"
				" ||, or &&\e[0m", STDERR_FILENO), 1);
	else if (svars->searching_redir_file)
		return (ft_putendl_fd("\e[1;91mSyntax Error: Missing file name after "
				"redirection operator\e[0m", STDERR_FILENO), 1);
	else if (svars->bracket_level)
		return (ft_putendl_fd("\e[1;91mSyntax Error: Missing closing "
				"parenthesis\e[0m", STDERR_FILENO), 1);
	return (0);
}

static bool	check_bracket_syntax(char *line, int bracket_level,
	int empty_brackets)
{
	if (bracket_level < 0)
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing opening parenthesis\e[0m",
			STDERR_FILENO);
		return (0);
	}
	else if (empty_brackets && line[0] == ')')
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Empty parenthesis\e[0m",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

bool	check_first_word(char *line, int *i, bool *sfw)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing command before ||\e[0m",
			STDERR_FILENO);
		return (0);
	}
	else if (line[*i] == '&' && line[*i + 1] == '&')
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing command before &&\e[0m",
			STDERR_FILENO);
		return (0);
	}
	else if (line[*i] == '|')
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing command before |\e[0m",
			STDERR_FILENO);
		return (0);
	}
	else if (line[*i] == '(')
		*sfw = true;
	return (1);
}

static bool	check_opening_syntax(char *line, bool sfw, bool srf, bool pfw)
{
	if (ft_strchr("|&", line[0]) && sfw)
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing command after |, ||, "
			"or &&\e[0m", STDERR_FILENO);
		return (0);
	}
	else if (ft_strchr("<>|&", line[0]) && srf)
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Missing file name after "
			"redirection operator\e[0m", STDERR_FILENO);
		return (0);
	}
	else if (line[0] == '&' && line[1] != '&')
	{
		ft_putendl_fd("\e[1;91mSyntax Error: Invalid operator &, please use "
			"&& instead\e[0m", STDERR_FILENO);
		return (0);
	}
	else if (line[0] == '(' && (!sfw || pfw))
	{
		ft_putendl_fd("\e[1;91mSyntax Error: unexpected '(' found\e[0m",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

bool	check_opening_and_bracket_syntax(t_syntax_vars *svars, char *line)
{
	if (!check_opening_syntax(line + svars->i,
			svars->searching_first_word, svars->searching_redir_file,
			svars->pipe_first_word))
		return (1);
	else if (!check_bracket_syntax(line + svars->i, svars->bracket_level,
			svars->empty_brackets))
		return (1);
	return (0);
}
