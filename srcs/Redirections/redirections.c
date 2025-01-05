/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:08:54 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/05 17:03:07 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_single_right(char *filename, t_ms_vars *ms_vars)
{
	int	fd;

	if (ms_vars->proc_type == PARENT && ms_vars->stdout_fd == STDOUT_FILENO)
	{
		ms_vars->stdout_fd = dup(STDOUT_FILENO);
		if (ms_vars->stdout_fd == -1)
			return (perror("dup"), 0);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP
			| S_IROTH | S_IWUSR);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	redir_single_left(char *filename, t_ms_vars *ms_vars)
{
	int	fd;

	if (ms_vars->proc_type == PARENT && ms_vars->stdin_fd == STDIN_FILENO)
	{
		ms_vars->stdin_fd = dup(STDIN_FILENO);
		if (ms_vars->stdin_fd == -1)
			return (perror("dup"), 0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	redir_double_right(char *filename, t_ms_vars *ms_vars)
{
	int	fd;

	if (ms_vars->proc_type == PARENT && ms_vars->stdout_fd == STDOUT_FILENO)
	{
		ms_vars->stdout_fd = dup(STDOUT_FILENO);
		if (ms_vars->stdout_fd == -1)
			return (perror("dup"), 0);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP
			| S_IROTH | S_IWUSR);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	redir_double_left(t_ms_vars *ms_vars)
{
	if (ms_vars->proc_type == PARENT && ms_vars->stdin_fd == STDIN_FILENO)
	{
		ms_vars->stdin_fd = dup(STDIN_FILENO);
		if (ms_vars->stdin_fd == -1)
			return (perror("dup"), 0);
	}
	if (dup2(ms_vars->heredoc_fd[ms_vars->pipe_number][0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		return (0);
	}
	return (1);
}

int	perform_redirection(char **filename, t_ms_vars *ms_vars)
{
	*filename = remove_quotes(*filename);
	if (!*filename)
		return (0);
	revert_transform(*filename);
	if (ms_vars->redirect == SINGLE_RIGHT)
	{
		if (!redir_single_right(*filename, ms_vars))
			return (0);
	}
	else if (ms_vars->redirect == DOUBLE_RIGHT)
	{
		if (!redir_double_right(*filename, ms_vars))
			return (0);
	}
	else if (ms_vars->redirect == SINGLE_LEFT)
	{
		if (!redir_single_left(*filename, ms_vars))
			return (0);
	}
	else
	{
		if (!redir_double_left(ms_vars))
			return (0);
	}
	return (1);
}
