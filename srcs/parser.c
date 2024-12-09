/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:57 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/04 20:25:20 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_ambiguous_redirections(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i] && i < 2)
		i++;
	if (i != 1)
	{
		ft_putendl_fd("\e[1;91mError: ambiguous redirection\e[0m",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void	add_to_argv(char **split_arr, t_ms_vars *ms_vars)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		ms_vars->exec_argv[ms_vars->argv_index] = remove_quotes(split_arr[i]);
		if (!ms_vars->exec_argv[ms_vars->argv_index])
		{
			free_2d_arr((void ***)&split_arr);
			ms_vars->exit_value = EXIT_FAILURE;
			exit_cleanup(ms_vars);
		}
		revert_transform(ms_vars->exec_argv[ms_vars->argv_index++]);
		i++;
	}
}

static void	get_exec_args(char **split_arr, t_ms_vars *ms_vars)
{
	int		num_elements;

	num_elements = count_split_elements(split_arr);
	if (num_elements > 0)
	{
		ms_vars->exec_argv = ft_realloc_str_arr(ms_vars->exec_argv, ms_vars->argv_index + num_elements + 1);
		if (!ms_vars->exec_argv)
		{
			free_2d_arr((void ***)&split_arr);
			exit_cleanup(ms_vars);
		}
		add_to_argv(split_arr, ms_vars);
	}
}

void	parse_cmd_redirects(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	char	**split_arr;

	if (stree->num_branches == 0)
		return ;
	branch = 0;
	while (branch < stree->num_branches)
	{
		if (stree->branches[branch]->type == HEREDOC_DELIMITER || stree->branches[branch]->type == HEREDOC_QUOTED_DELIMITER)
			perform_heredoc(revert_transform(stree->branches[branch]->value), ms_vars, stree->branches[branch]->type);
		branch++;
	}
	branch = 0;
	ms_vars->argv_index = 0;
	split_arr = NULL;
	modify_expansions_if_export(stree);
	while (branch < stree->num_branches)
	{
		if (stree->branches[branch]->type == WORD)
		{
			split_arr = do_expansions(stree->branches[branch]->value, ms_vars);
			if (!split_arr)
				exit_cleanup(ms_vars);
			get_exec_args(split_arr, ms_vars);
			free(split_arr);
			split_arr = NULL;
		}
		else if (stree->branches[branch]->type == T_FILE)
		{
			split_arr = do_expansions(stree->branches[branch]->value, ms_vars);
			if (!split_arr)
				exit_cleanup(ms_vars);
			if (check_ambiguous_redirections(split_arr) || !perform_redirection\
			(&split_arr[0], ms_vars))
			{
				ms_vars->exit_value = EXIT_FAILURE;
				free_2d_arr((void ***)&split_arr);
				if (ms_vars->proc_type == CHILD)
					exit_cleanup(ms_vars);
				else
					return (free_2d_arr((void ***)&ms_vars->exec_argv));
			}
			free_2d_arr((void ***)&split_arr);
		}
		else if (stree->branches[branch]->type == HEREDOC_DELIMITER || stree->branches[branch]->type == HEREDOC_QUOTED_DELIMITER)
			perform_redirection(&stree->branches[branch]->value, ms_vars);
		else if (stree->branches[branch]->type == SINGLE_RIGHT)
			ms_vars->redirect = SINGLE_RIGHT;
		else if (stree->branches[branch]->type == DOUBLE_RIGHT)
			ms_vars->redirect = DOUBLE_RIGHT;
		else if (stree->branches[branch]->type == SINGLE_LEFT)
			ms_vars->redirect = SINGLE_LEFT;
		else if (stree->branches[branch]->type == DOUBLE_LEFT)
			ms_vars->redirect = DOUBLE_LEFT;
		branch++;
	}
	if (ms_vars->exec_argv)
	{
		if (!check_cmd_is_builtin(ms_vars))
		{
			if (ms_vars->proc_type == PARENT)
				fork_wait_single_process(ms_vars);
			else
				exec_cmd(ms_vars);
		}
		free_2d_arr((void ***)&ms_vars->exec_argv);
	}
	else
		ms_vars->exit_value = EXIT_SUCCESS;
}

void	parse_tree(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;

	branch = 0;
	if (stree->type == PIPE)
	{
		if (stree->num_branches > 1)
		{
			ms_vars->pid_arr = ft_calloc(stree->num_branches, sizeof(pid_t));
			if (!ms_vars->pid_arr)
				exit_cleanup(ms_vars);
			fork_child_processes(stree, ms_vars);
			wait_child_processes(stree, ms_vars);
			free(ms_vars->pid_arr);
		}
		else
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
			return ;
		}
	}
	while (branch < stree->num_branches && stree->type != PIPE)
	{
		if (stree->branches[branch]->type == AND && ms_vars->exit_value != EXIT_SUCCESS)
			branch += 2;
		else if (stree->branches[branch]->type == OR && ms_vars->exit_value == EXIT_SUCCESS)
			branch += 2;
		else
			parse_tree(stree->branches[branch++], ms_vars);
	}
}
