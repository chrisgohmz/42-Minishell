/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:38:40 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/17 21:45:47 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	modify_expansions_if_export(t_syntax_tree *stree)
{
	int	i;

	i = 0;
	while (i < stree->num_branches)
	{
		if (stree->branches[i]->type == WORD)
		{
			if (ft_strncmp("export", stree->branches[i]->value, sizeof("export")) == 0)
				break;
			else
				return ;
		}
		i++;
	}
	while (++i < stree->num_branches)
	{
		if (stree->branches[i]->type == WORD)
			disable_value_word_splitting(stree->branches[i]->value);
	}
}

void	fork_wait_single_process(t_ms_vars *ms_vars)
{
	pid_t	pid;
	int		status;

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

void	fork_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	int 	fds[2];
	pid_t	pid;
	int 	temp_fd;
	//int status;

	//current problem: shell will exit with piped commands because parent's stdin fd was replaced, need to make sure only the child calls dup2
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
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (branch == 0) //child of 1st cmd
			{
				if (dup2(fds[1], STDOUT_FILENO) == -1)
					perror("dup2"); // to send output of 1st cmd to write end of the pipe
				close(fds[0]);
				close(fds[1]);
				parse_cmd_redirects(stree->branches[branch], ms_vars);
				exit_cleanup(ms_vars);
			}
			else if (branch == (stree->num_branches - 1)) //child of last cmd
			{
				if (dup2(temp_fd, STDIN_FILENO) == -1)
					perror("dup2");
				close(temp_fd);
				close(fds[0]);
				close(fds[1]);
				parse_cmd_redirects(stree->branches[branch], ms_vars);
				exit_cleanup(ms_vars);
			}
			else
			{
				if (dup2(temp_fd, STDIN_FILENO) == -1)
					perror("dup2");
				if (dup2(fds[1], STDOUT_FILENO) == -1)
					perror("dup2");
				close(temp_fd);
				close(fds[0]);
				close(fds[1]);
				parse_cmd_redirects(stree->branches[branch], ms_vars);
				exit_cleanup(ms_vars);
			}
		}
		else if(branch == (stree->num_branches - 1))//exit to parent
		{
			if (temp_fd != -1)
				close(temp_fd);
			close(fds[0]);
			close(fds[1]);
		}
		else //exit to parent
		{
			if (temp_fd != -1)
				close(temp_fd);
			temp_fd = fds[0];
			close(fds[1]);
		}
		ms_vars->pipe_number++;
		ms_vars->pid_arr[branch++] = pid;
	}
}

int	check_cmd_is_builtin(t_ms_vars *ms_vars)
{
	if (ft_strncmp(ms_vars->exec_argv[0], "cd", sizeof("cd")) == 0)
		return (cd_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "pwd", sizeof("pwd")) == 0)
		return (pwd_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "echo", sizeof("echo")) == 0)
		return (echo_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "export", sizeof("export")) == 0)
		return (export_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "unset", sizeof("unset")) == 0)
		return (unset_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "env", sizeof("env")) == 0)
		return (env_builtin(ms_vars), 1);
	else if (ft_strncmp(ms_vars->exec_argv[0], "exit", sizeof("exit")) == 0)
		return (exit_builtin(ms_vars), 1);
	return (0);
}
