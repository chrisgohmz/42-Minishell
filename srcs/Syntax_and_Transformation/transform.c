/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:41:00 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/02 20:43:23 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	revert_transform2(char *token)
{
	if (*token == ESC_AND)
		*token = '&';
	else if (*token == ESC_OPEN_BRACKET)
		*token = '(';
	else if (*token == ESC_CLOSE_BRACKET)
		*token = ')';
	else if (*token == ESC_DOLLAR)
		*token = '$';
	else if (*token == DQUOTE_DOLLAR)
		*token = '$';
	else if (*token == ESC_WILDCARD)
		*token = '*';
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
		else if (token[i] == ESC_DQUOTE || token[i] == DQUOTE)
			token[i] = '"';
		else if (token[i] == ESC_SQUOTE || token[i] == SQUOTE)
			token[i] = '\'';
		else if (token[i] == ESC_PIPE)
			token[i] = '|';
		else if (token[i] == ESC_RIGHT)
			token[i] = '>';
		else if (token[i] == ESC_LEFT)
			token[i] = '<';
		else
			revert_transform2(token + i);
		i++;
	}
	return (token);
}

static void	transform_special_char2(char *c, int within_squotes,
	int within_dquotes)
{
	if ((within_squotes || within_dquotes) && *c == '&')
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
	else
		transform_special_char2(c, within_squotes, within_dquotes);
}
