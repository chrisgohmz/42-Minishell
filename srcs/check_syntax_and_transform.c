/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_transform.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:35:27 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/04 17:52:35 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_first_word(char *line, int *i, bool *sfw)
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

char	*revert_transform(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == ESC_SPACE)
			token[i] = ' ';
		else if (token[i] == ESC_TAB)
			token[i] = '\t';
		else if (token[i] == ESC_DQUOTE)
			token[i] = '"';
		else if (token[i] == ESC_SQUOTE)
			token[i] = '\'';
		else if (token[i] == ESC_PIPE)
			token[i] = '|';
		else if (token[i] == ESC_RIGHT)
			token[i] = '>';
		else if (token[i] == ESC_LEFT)
			token[i] = '<';
		else if (token[i] == ESC_AND)
			token[i] = '&';
		else if (token[i] == ESC_OPEN_BRACKET)
			token[i] = '(';
		else if (token[i] == ESC_CLOSE_BRACKET)
			token[i] = ')';
		else if (token[i] == ESC_DOLLAR)
			token[i] = '$';
		else if (token[i] == DQUOTE_DOLLAR)
			token[i] = '$';
		else if (token[i] == ESC_WILDCARD)
			token[i] = '*';
		i++;
	}
	return (token);
}

int	check_redirection_pipe_syntax(char *line, bool sfw, bool srf, bool pfw)
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

void	transform_special_char(char *c, int within_squotes, int within_dquotes)
{
	if ((within_squotes || within_dquotes) && *c == ' ')
		*c = ESC_SPACE;
	else if ((within_squotes || within_dquotes) && *c == '\t')
		*c = ESC_TAB;
	else if (within_squotes && *c == '"')
		*c = ESC_DQUOTE;
	else if (within_dquotes && *c == '\'')
		*c = ESC_SQUOTE;
	else if ((within_squotes || within_dquotes) && *c == '|')
		*c = ESC_PIPE;
	else if ((within_squotes || within_dquotes) && *c == '>')
		*c = ESC_RIGHT;
	else if ((within_squotes || within_dquotes) && *c == '<')
		*c = ESC_LEFT;
	else if ((within_squotes || within_dquotes) && *c == '&')
		*c = ESC_AND;
	else if ((within_squotes || within_dquotes) && *c == '(')
		*c = ESC_OPEN_BRACKET;
	else if ((within_squotes || within_dquotes) && *c == ')')
		*c = ESC_CLOSE_BRACKET;
	else if (within_squotes && *c == '$')
		*c = ESC_DOLLAR;
	else if (within_dquotes && *c == '$')
		*c = DQUOTE_DOLLAR;
	else if ((within_squotes || within_dquotes) && *c == '*')
		*c = ESC_WILDCARD;
}

int	check_syntax_and_transform_line(char *line)
{
	int		i;
	bool	searching_first_word;
	bool	pipe_first_word;
	bool	searching_redir_file;
	bool	within_squotes;
	bool	within_dquotes;
	int		bracket_level;
	bool	empty_brackets;

	i = 0;
	searching_first_word = false;
	pipe_first_word = false;
	searching_redir_file = false;
	within_squotes = false;
	within_dquotes = false;
	bracket_level = 0;
	empty_brackets = false;
	if (!check_first_word(line, &i, &searching_first_word))
		return (1);
	while (line[i])
	{
		if (!within_squotes && line[i] == '"')
		{
			within_dquotes = !within_dquotes;
			line[i] = DQUOTE;
		}
		else if (!within_dquotes && line[i] == '\'')
		{
			within_squotes = !within_squotes;
			line[i] = SQUOTE;
		}
		else if (!within_dquotes && !within_squotes && line[i] == '(')
			bracket_level++;
		else if (!within_dquotes && !within_squotes && line[i] == ')')
			bracket_level--;
		transform_special_char(line + i, within_squotes, within_dquotes);
		if (!check_redirection_pipe_syntax(line + i, searching_first_word, searching_redir_file, pipe_first_word))
			return (1);
		else if (!check_bracket_syntax(line + i, bracket_level, empty_brackets))
			return (1);
		if (searching_first_word && !ft_strchr(" \t<>(", line[i]))
			searching_first_word = false;
		else if (!searching_first_word && (line[i] == '|' || (line[i] == '&' && line[i + 1] == '&') || line[i] == '('))
			searching_first_word = true;
		else if (!searching_redir_file && ft_strchr("<>", line[i]))
			searching_redir_file = true;
		else if (searching_redir_file && !ft_strchr(" \t", line[i]))
			searching_redir_file = false;
		if (line[i] == '|' && line[i + 1] != '|' && !pipe_first_word)
			pipe_first_word = true;
		else if (pipe_first_word && !ft_strchr(" \t", line[i]))
			pipe_first_word = false;
		if (line[i] == '>' && line[i + 1] == '>')
			i++;
		else if (line[i] == '<' && line[i + 1] == '<')
			i++;
		else if (line[i] == '|' && line[i + 1] == '|')
			i++;
		else if (line[i] == '&' && line[i + 1] == '&')
			i++;
		else if (line[i] == '(')
			empty_brackets = true;
		else if (empty_brackets && !ft_strchr(" \t", line[i]))
			empty_brackets = false;
		i++;
	}
	if (within_squotes || within_dquotes)
		return (ft_putendl_fd("\e[1;91mSyntax Error: unclosed quotes\e[0m",
				STDERR_FILENO), 1);
	else if (searching_first_word)
		return (ft_putendl_fd("\e[1;91mSyntax Error: Missing command after |,"
				" ||, or &&\e[0m", STDERR_FILENO), 1);
	else if (searching_redir_file)
		return (ft_putendl_fd("\e[1;91mSyntax Error: Missing file name after "
				"redirection operator\e[0m", STDERR_FILENO), 1);
	else if (bracket_level)
		return (ft_putendl_fd("\e[1;91mSyntax Error: Missing closing "
				"parenthesis\e[0m", STDERR_FILENO), 1);
	return (0);
}
