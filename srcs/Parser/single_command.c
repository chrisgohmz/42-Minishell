/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:34:00 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 18:20:59 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	wait_single_process(pid_t pid, t_ms_vars *ms_vars)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_vars->exit_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		ms_vars->exit_value = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
		{
			g_sigint = 1;
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}

void	fork_single_process(t_ms_vars *ms_vars)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_cmd(ms_vars);
		exit_cleanup(ms_vars);
	}
	wait_single_process(pid, ms_vars);
}

void	handle_single_command(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	parse_cmd_redirects(stree->branches[0], ms_vars);
	if (ms_vars->stdout_fd != STDOUT_FILENO)
	{
		if (dup2(ms_vars->stdout_fd, STDOUT_FILENO) < 0)
			perror("dup2");
		close(ms_vars->stdout_fd);
		ms_vars->stdout_fd = STDOUT_FILENO;
	}
	if (ms_vars->stdin_fd != STDIN_FILENO)
	{
		if (dup2(ms_vars->stdin_fd, STDIN_FILENO) < 0)
			perror("dup2");
		close(ms_vars->stdin_fd);
		ms_vars->stdin_fd = STDIN_FILENO;
	}
	close_heredoc_fds(ms_vars);
	reset_heredoc_fds(ms_vars);
}
