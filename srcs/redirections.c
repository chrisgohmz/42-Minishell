/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:08:54 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/09 13:47:57 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	perform_heredoc(char *delimiter, t_ms_vars *ms_vars, t_token_type delim_type)
{
	(void)delimiter;
	(void)ms_vars;
	(void)delim_type;
	if (delim_type == HEREDOC_DELIMITER)
	{
		//todo
	}
	else if (delim_type == HEREDOC_QUOTED_DELIMITER)
	{
		//todo
	}
}

int	perform_redirection(char *filename, t_ms_vars *ms_vars)
{
	(void)filename;
	if (ms_vars->redirect == SINGLE_RIGHT)
	{
		//todo
	}
	else if (ms_vars->redirect == DOUBLE_RIGHT)
	{
		//todo
	}
	else if (ms_vars->redirect == SINGLE_LEFT)
	{
		//todo
	}
	return (1);
}
