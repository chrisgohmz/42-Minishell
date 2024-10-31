/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_transform.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:35:27 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/31 18:21:34 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_first_word(char *line, int *i, int *sfw, int *is_export)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		printf("Syntax Error: Missing command before ||\n");
		return (0);
	}
	else if (line[*i] == '&' && line[*i + 1] == '&')
	{
		printf("Syntax Error: Missing command before &&\n");
		return (0);
	}
	else if (line[*i] == '|')
	{
		printf("Syntax Error: Missing command before |\n");
		return (0);
	}
	else if (line[*i] == '(')
		*sfw = 1;
	else if (!ft_strncmp(line + *i, "export ", 7) || !ft_strncmp(line + *i, "export\t", 7))
		*is_export = 1;
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

int	check_redirection_pipe_syntax(char *line, int sfw, int srf, int pfw)
{
	if (ft_strchr("|&", line[0]) && sfw)
	{
		printf("Syntax Error: Missing command after |, ||, or &&\n");
		return (0);
	}
	else if (ft_strchr("<>|&", line[0]) && srf)
	{
		printf("Syntax Error: Missing file name after redirection operator\n");
		return (0);
	}
	else if (line[0] == '&' && line[1] != '&')
	{
		printf("Syntax Error: Invalid operator &, please use && instead\n");
		return (0);
	}
	else if (line[0] == '(' && (!sfw || pfw))
	{
		printf("Syntax Error: unexpected '(' found\n");
		return (0);
	}
	return (1);
}

void	transform_special_char(char *c, int within_squotes, int within_dquotes, int exporting_value)
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
	else if ((within_dquotes || exporting_value) && *c == '$')
		*c = DQUOTE_DOLLAR;
	else if ((within_squotes || within_dquotes || exporting_value) && *c == '*')
		*c = ESC_WILDCARD;
}

int	check_syntax_and_transform_line(char *line)
{
	int	i;
	int	searching_first_word;
	int	pipe_first_word;
	int	searching_redir_file;
	int	within_squotes;
	int	within_dquotes;
	int	bracket_level;
	int	empty_brackets;
	int	is_export;
	int	exporting_value;

	i = 0;
	searching_first_word = 0;
	pipe_first_word = 0;
	searching_redir_file = 0;
	within_squotes = 0;
	within_dquotes = 0;
	bracket_level = 0;
	empty_brackets = 0;
	is_export = 0;
	exporting_value = 0;
	if (!check_first_word(line, &i, &searching_first_word, &is_export))
		return (1);
	while (line[i])
	{
		if (!within_squotes && line[i] == '"')
			within_dquotes = !within_dquotes;
		else if (!within_dquotes && line[i] == '\'')
			within_squotes = !within_squotes;
		else if (!within_dquotes && !within_squotes && line[i] == '(')
			bracket_level++;
		else if (!within_dquotes && !within_squotes && line[i] == ')')
			bracket_level--;
		else if (is_export && line[i] == '=')
			exporting_value = 1;
		else if (exporting_value && ft_strchr(" \t", line[i]))
			exporting_value = 0;
		else if (is_export && ft_strchr("|&", line[i]))
			is_export = 0;
		transform_special_char(line + i, within_squotes, within_dquotes, exporting_value);
		if (!check_redirection_pipe_syntax(line + i, searching_first_word, searching_redir_file, pipe_first_word))
			return (1);
		else if (!check_bracket_syntax(line + i, bracket_level, empty_brackets))
			return (1);
		if (searching_first_word && !ft_strchr(" \t<>(", line[i]))
			searching_first_word = 0;
		else if (!searching_first_word && (line[i] == '|' || (line[i] == '&' && line[i + 1] == '&') || line[i] == '('))
			searching_first_word = 1;
		else if (!searching_redir_file && ft_strchr("<>", line[i]))
			searching_redir_file = 1;
		else if (searching_redir_file && !ft_strchr(" \t", line[i]))
			searching_redir_file = 0;
		if (line[i] == '|' && line[i + 1] != '|' && !pipe_first_word)
			pipe_first_word = 1;
		else if (pipe_first_word && !ft_strchr(" \t", line[i]))
			pipe_first_word = 0;
		if (line[i] == '>' && line[i + 1] == '>')
			i++;
		else if (line[i] == '<' && line[i + 1] == '<')
			i++;
		else if (line[i] == '|' && line[i + 1] == '|')
			i++;
		else if (line[i] == '&' && line[i + 1] == '&')
			i++;
		else if (line[i] == '(')
			empty_brackets = 1;
		else if (empty_brackets && !ft_strchr(" \t", line[i]))
			empty_brackets = 0;
		i++;
	}
	if (within_squotes || within_dquotes)
	{
		printf("Syntax Error: unclosed quotes\n");
		return (1);
	}
	if (searching_first_word)
	{
		printf("Syntax Error: Missing command after |, ||, or &&\n");
		return (1);
	}
	else if (searching_redir_file)
	{
		printf("Syntax Error: Missing file name after redirection operator\n");
		return (1);
	}
	else if (bracket_level)
	{
		printf("Syntax Error: Missing closing parenthesis\n");
		return (1);
	}
	return (0);
}
