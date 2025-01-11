/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:30:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/11 15:33:36 by lpwi             ###   ########.fr       */
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

static void	pipe_parent(t_syntax_tree *stree, int branch, int *temp_fd,
			int *fds)
{
	if (branch == (stree->num_branches - 1))
	{
		if (*temp_fd != -1)
			close(*temp_fd);
		close(fds[0]);
		close(fds[1]);
	}
	else
	{
		if (*temp_fd != -1)
			close(*temp_fd);
		*temp_fd = fds[0];
		close(fds[1]);
	}
}

static void	pipe_child(t_syntax_tree *stree, int branch, int *fds, int temp_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (branch == 0)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else if (branch == (stree->num_branches - 1))
	{
		if (dup2(temp_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(temp_fd);
	}
	else
	{
		if (dup2(temp_fd, STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(temp_fd);
	}
	close(fds[0]);
	close(fds[1]);
}

void	fork_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	int		fds[2];
	pid_t	pid;
	int		temp_fd;

	branch = 0;
	temp_fd = -1;
	while (branch < stree->num_branches)
	{
		if (pipe(fds) < 0)
			return (perror("pipe"));
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		else if (pid == 0)
		{
			ms_vars->proc_type = CHILD;
			pipe_child(stree, branch, fds, temp_fd);
			parse_cmd_redirects(stree->branches[branch], ms_vars);
		}
		else
			pipe_parent(stree, branch, &temp_fd, fds);
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
