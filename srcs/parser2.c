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
		exec_cmd(ms_vars);
		exit_cleanup(ms_vars);
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

void	fork_child_processes(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	int 	fds[2];
	pid_t	pid;
	//int status;

	//current problem: shell will exit with piped commands because parent's stdin fd was replaced, need to make sure only the child calls dup2
	branch = 0;
	while (branch < stree->num_branches)
	{
		if(branch != (stree->num_branches - 1))
		{
			pipe(fds);
			// signal(SIGINT, SIG_IGN);
			// signal(SIGQUIT, SIG_IGN);
			pid = fork(); // may not need to fork since parse_cmd is creating a fork? cgoh: u do. parse_cmd_redirects doesn't do any forks for piped commands
			if (pid < 0)
			{
				perror("fork");
				return ;
			}
			else if (pid == 0)
			{
				ms_vars->proc_type = CHILD;
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				close(fds[1]);
				parse_cmd_redirects(stree->branches[branch], ms_vars);
				// exit_cleanup(ms_vars);
			}
			else //exit to parent
			{
				dup2(fds[0], STDIN_FILENO);
				close(fds[0]);
				close(fds[1]);
			}
			//waitpid(pid, &status, 0); not needed, handled in function wait_child_processes
		}
		else
			parse_cmd_redirects(stree->branches[branch], ms_vars);
		ms_vars->pipe_number++;
		ms_vars->pid_arr[branch++] = pid;
		if (ms_vars->heredoc_fd[ms_vars->pipe_number][0] > -1)
			close(ms_vars->heredoc_fd[ms_vars->pipe_number][0]);
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
