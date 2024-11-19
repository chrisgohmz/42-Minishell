/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:08:54 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/19 19:33:57 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redir_single_right(char *filename, t_ms_vars *ms_vars)
{
	int	fd1;

	fd1 = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP
			| S_IROTH | S_IWUSR);
	if (fd1 == -1)
	{
		perror(filename);
		return (0);
	}
	if (ms_vars->proc_type == CHILD)
	{
		if (dup2(fd1, 1) < 0)
		{
			perror("dup2");
			close(fd1);
			return (0);
		}
		close(fd1);
	}
	else
		ms_vars->fd_out = fd1;
	return (1);
}

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
	if (ms_vars->redirect == SINGLE_RIGHT)
	{
		if (!redir_single_right(filename, ms_vars))
			return (0);
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
