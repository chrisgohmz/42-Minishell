/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:30:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/11 17:15:19 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		i;
	int		status;
	bool	line_printed;

	i = 0;
	line_printed = false;
	while (i < stree->num_branches)
	{
		waitpid(ms_vars->pid_arr[i], &status, 0);
		if (WIFEXITED(status))
			ms_vars->exit_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			ms_vars->exit_value = 128 + WTERMSIG(status);
			if (!line_printed && WTERMSIG(status) == SIGINT)
			{
				g_sigint = 1;
				ft_putchar_fd('\n', STDERR_FILENO);
			}
			else if (!line_printed && WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
			line_printed = true;
		}
		i++;
	}
}

static void	pipe_parent(t_syntax_tree *stree, int branch, t_pipe_fds *pipe_fds)
{
	if (branch == (stree->num_branches - 1))
	{
		if (pipe_fds->temp_fd != -1)
			close(pipe_fds->temp_fd);
		close(pipe_fds->fds[0]);
		close(pipe_fds->fds[1]);
	}
	else
	{
		if (pipe_fds->temp_fd != -1)
			close(pipe_fds->temp_fd);
		pipe_fds->temp_fd = pipe_fds->fds[0];
		close(pipe_fds->fds[1]);
	}
}

static void	pipe_child(t_syntax_tree *stree, t_ms_vars *ms_vars, int branch,
			t_pipe_fds *pipe_fds)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ms_vars->proc_type = CHILD;
	if (branch == 0)
	{
		if (dup2(pipe_fds->fds[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else if (branch == (stree->num_branches - 1))
	{
		if (dup2(pipe_fds->temp_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(pipe_fds->temp_fd);
	}
	else
	{
		if (dup2(pipe_fds->temp_fd, STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(pipe_fds->fds[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(pipe_fds->temp_fd);
	}
	close(pipe_fds->fds[0]);
	close(pipe_fds->fds[1]);
}

void	fork_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int			branch;
	pid_t		pid;
	t_pipe_fds	pipe_fds;

	branch = 0;
	pipe_fds.temp_fd = -1;
	while (branch < stree->num_branches)
	{
		if (pipe(pipe_fds.fds) < 0)
			return (perror("pipe"));
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		else if (pid == 0)
		{
			pipe_child(stree, ms_vars, branch, &pipe_fds);
			parse_cmd_redirects(stree->branches[branch], ms_vars);
			exit_cleanup(ms_vars);
		}
		else
			pipe_parent(stree, branch, &pipe_fds);
		ms_vars->pipe_number++;
		ms_vars->pid_arr[branch++] = pid;
	}
}

void	handle_piped_commands(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	ms_vars->pid_arr = ft_calloc(stree->num_branches, sizeof(pid_t));
	if (!ms_vars->pid_arr)
		exit_cleanup(ms_vars);
	fork_child_processes(stree, ms_vars);
	wait_child_processes(stree, ms_vars);
	free(ms_vars->pid_arr);
	close_heredoc_fds(ms_vars);
	reset_heredoc_fds(ms_vars);
}
