/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_transform.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:35:27 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/18 18:55:57 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_first_word_is_pipe(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '|')
	{
		printf("Syntax Error: Missing command before pipe\n");
		return (0);
	}
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
		else if (token[i] == ESC_DOLLAR)
			token[i] = '$';
		else if (token[i] == DQUOTE_DOLLAR)
			token[i] = '$';
		i++;
	}
	return (token);
}

int	check_redirection_pipe_syntax(char *line, int separated)
{
	int	error;

	error = 0;
	if ((line[0] == '<' || line[0] == '>' || line[0] == '|') && separated)
		error = 1;
	else if (line[0] == '<' && ft_strchr(">|", line[1]))
		error = 1;
	else if (line[0] == '>' && ft_strchr("<|", line[1]))
		error = 1;
	else if (line[0] == '|' && ft_strchr("<>", line[1]))
		error = 1;
	else if (line[0] == '<' && line[1] == '<' && line[2] == '<')
		error = 1;
	else if (line[0] == '>' && line[1] == '>' && line[2] == '>')
		error = 1;
	else if (line[0] == '|' && line[1] == '|' && line[2] == '|')
		error = 1;
	if (error)
	{
		printf("Redirection/Pipe Syntax Error\n");
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
	else if (within_squotes && *c == '$')
		*c = ESC_DOLLAR;
	else if (within_dquotes && *c == '$')
		*c = DQUOTE_DOLLAR;
}

int	check_syntax_and_transform_line(char *line)
{
	int	i;
	int	separated;
	int	redirection_or_pipe;
	int	within_squotes;
	int	within_dquotes;

	i = 0;
	separated = 0;
	redirection_or_pipe = 0;
	within_squotes = 0;
	within_dquotes = 0;
	if (!check_first_word_is_pipe(line, &i))
		return (1);
	while (line[i])
	{
		if (!within_squotes && line[i] == '"')
			within_dquotes = 1 - within_dquotes;
		else if (!within_dquotes && line[i] == '\'')
			within_squotes = 1 - within_squotes;
		transform_special_char(line + i, within_squotes, within_dquotes);
		if (!check_redirection_pipe_syntax(line + i, separated))
			return (1);
		separated = (redirection_or_pipe && ft_strchr(" \t", line[i]) != NULL);
		redirection_or_pipe = (separated || ft_strchr("<>|", line[i]) != NULL);
		i++;
	}
	if (within_squotes || within_dquotes)
	{
		printf("Syntax Error: unclosed quotes\n");
		return (1);
	}
	if (redirection_or_pipe)
	{
		printf("Syntax Error: Missing argument after Pipe/Redirection\n");
		return (1);
	}
	return (0);
}
