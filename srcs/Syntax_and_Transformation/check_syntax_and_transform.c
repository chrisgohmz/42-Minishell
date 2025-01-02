/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_and_transform.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:35:27 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/02 20:46:38 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_svars2(t_syntax_vars *svars, char *line)
{
	if (line[svars->i] == '>' && line[svars->i + 1] == '>')
		svars->i++;
	else if (line[svars->i] == '<' && line[svars->i + 1] == '<')
		svars->i++;
	else if (line[svars->i] == '|' && line[svars->i + 1] == '|')
		svars->i++;
	else if (line[svars->i] == '&' && line[svars->i + 1] == '&')
		svars->i++;
	else if (line[svars->i] == '(')
		svars->empty_brackets = true;
	else if (svars->empty_brackets && !ft_strchr(" \t", line[svars->i]))
		svars->empty_brackets = false;
}

void	update_svars(t_syntax_vars *svars, char *line)
{
	if (svars->searching_first_word && !ft_strchr(" \t<>(", line[svars->i]))
		svars->searching_first_word = false;
	else if (!svars->searching_first_word && (line[svars->i] == '|'
			|| (line[svars->i] == '&' && line[svars->i + 1] == '&')
			|| line[svars->i] == '('))
		svars->searching_first_word = true;
	else if (!svars->searching_redir_file && ft_strchr("<>", line[svars->i]))
		svars->searching_redir_file = true;
	else if (svars->searching_redir_file && !ft_strchr(" \t", line[svars->i]))
		svars->searching_redir_file = false;
	if (line[svars->i] == '|' && line[svars->i + 1] != '|'
		&& !svars->pipe_first_word)
		svars->pipe_first_word = true;
	else if (svars->pipe_first_word && !ft_strchr(" \t", line[svars->i]))
		svars->pipe_first_word = false;
	update_svars2(svars, line);
}

static void	update_quotes_and_update_bracket_level(t_syntax_vars *svars,
	char *line)
{
	if (!svars->within_squotes && line[svars->i] == '"')
	{
		svars->within_dquotes = !svars->within_dquotes;
		line[svars->i] = DQUOTE;
	}
	else if (!svars->within_dquotes && line[svars->i] == '\'')
	{
		svars->within_squotes = !svars->within_squotes;
		line[svars->i] = SQUOTE;
	}
	else if (!svars->within_dquotes && !svars->within_squotes
		&& line[svars->i] == '(')
		svars->bracket_level++;
	else if (!svars->within_dquotes && !svars->within_squotes
		&& line[svars->i] == ')')
		svars->bracket_level--;
}

static void	init_svars(t_syntax_vars *svars)
{
	svars->i = 0;
	svars->searching_first_word = false;
	svars->pipe_first_word = false;
	svars->searching_redir_file = false;
	svars->within_squotes = false;
	svars->within_dquotes = false;
	svars->bracket_level = 0;
	svars->empty_brackets = false;
}

int	check_syntax_and_transform_line(char *line)
{
	t_syntax_vars	svars;

	init_svars(&svars);
	if (!check_first_word(line, &svars.i, &svars.searching_first_word))
		return (1);
	while (line[svars.i])
	{
		update_quotes_and_update_bracket_level(&svars, line);
		transform_special_char(line + svars.i, svars.within_squotes,
			svars.within_dquotes);
		if (check_opening_and_bracket_syntax(&svars, line))
			return (1);
		update_svars(&svars, line);
		svars.i++;
	}
	if (check_closing_syntax(&svars))
		return (1);
	return (0);
}
