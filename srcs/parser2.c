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

void	fork_wait_single_process(t_ms_vars *ms_vars)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		error_cleanup(ms_vars);
	}
	else if (pid == 0)
	{
		exec_cmd(ms_vars);
		error_cleanup(ms_vars);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_vars->exit_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms_vars->exit_value = 128 + WTERMSIG(status);
}

void	wait_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int	i;
	int	status;

	i = 0;
	while (i < stree->num_branches)
	{
		waitpid(ms_vars->pid_arr[i], &status, 0);
		if (WIFEXITED(status))
			ms_vars->exit_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms_vars->exit_value = 128 + WTERMSIG(status);
		i++;
	}
}

int	fork_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	pid_t	pid;

	branch = 0;
	while (branch < stree->num_branches)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			error_cleanup(ms_vars);
		}
		else if (pid == 0)
		{
			ms_vars->proc_type = CHILD;
			parse_cmd_redirects(stree->branches[branch], ms_vars);
			error_cleanup(ms_vars);
		}
		ms_vars->pid_arr[branch++] = pid;
	}
	return (1);
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
