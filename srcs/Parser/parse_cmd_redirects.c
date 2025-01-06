/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:36:42 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 21:07:15 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_cmd_is_builtin(t_ms_vars *ms_vars)
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

static void	close_heredocs_and_execute_cmd(t_ms_vars *ms_vars)
{
	if (ms_vars->heredoc_fd[ms_vars->pipe_number][0] > -1)
	{
		close(ms_vars->heredoc_fd[ms_vars->pipe_number][0]);
		ms_vars->heredoc_fd[ms_vars->pipe_number][0] = -1;
	}
	if (ms_vars->exec_argv)
	{
		if (!check_cmd_is_builtin(ms_vars))
		{
			if (ms_vars->proc_type == PARENT)
				fork_single_process(ms_vars);
			else
				exec_cmd(ms_vars);
		}
		free_2d_arr((void ***)&ms_vars->exec_argv);
	}
	else
		ms_vars->exit_value = EXIT_SUCCESS;
}

static bool	handle_token_type(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	if (stree->type == WORD)
		handle_word_token(stree->value, ms_vars);
	else if (stree->type == T_FILE)
	{
		if (!handle_file_token(stree->value, ms_vars))
			return (false);
	}
	else if (stree->type == HEREDOC_DELIMITER
		|| stree->type == HEREDOC_QUOTED_DELIMITER)
	{
		if (!handle_heredoc_token(&stree->value, ms_vars))
			return (false);
	}
	else if (stree->type == SINGLE_RIGHT)
		ms_vars->redirect = SINGLE_RIGHT;
	else if (stree->type == DOUBLE_RIGHT)
		ms_vars->redirect = DOUBLE_RIGHT;
	else if (stree->type == SINGLE_LEFT)
		ms_vars->redirect = SINGLE_LEFT;
	else if (stree->type == DOUBLE_LEFT)
		ms_vars->redirect = DOUBLE_LEFT;
	return (true);
}

void	parse_cmd_redirects(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;

	if (stree->num_branches == 0)
		return ;
	branch = -1;
	modify_expansions_if_export(stree);
	while (++branch < stree->num_branches)
		if (!handle_token_type(stree->branches[branch], ms_vars))
			return ;
	close_heredocs_and_execute_cmd(ms_vars);
}
