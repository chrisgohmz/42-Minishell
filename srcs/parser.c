/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:57 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/09 18:15:59 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_ambigious_redirections(char *expanded_str, t_ms_vars *ms_vars)
{
	char	**split_arr;

	split_arr = ft_multi_split(expanded_str, " \t");
	if (!split_arr)
		error_cleanup(ms_vars);
	if (count_split_elements(split_arr) > 1)
	{
		printf("Error: Ambigious redirection\n");
		free_2d_malloc_array(&split_arr);
		error_cleanup(ms_vars);
		exit(EXIT_FAILURE);
	}
	free_2d_malloc_array(&split_arr);
}

static void	add_to_argv(char **split_arr, t_ms_vars *ms_vars)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		ms_vars->exec_argv[ms_vars->argv_index++] = split_arr[i];
		i++;
	}
}

static void	get_exec_args(char *expanded_str, t_ms_vars *ms_vars)
{
	char	**split_arr;
	int		num_elements;

	split_arr = ft_multi_split(expanded_str, " \t");
	free(expanded_str);
	if (!split_arr)
		error_cleanup(ms_vars);
	num_elements = count_split_elements(split_arr);
	ms_vars->exec_argv = ft_realloc_str_arr(ms_vars->exec_argv, ms_vars->argv_index + num_elements + 1);
	if (!ms_vars->exec_argv)
	{
		free_2d_malloc_array(&split_arr);
		error_cleanup(ms_vars);
	}
	add_to_argv(split_arr, ms_vars);
	free(split_arr);
}

void	parse_cmd_redirects(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	char	*expanded_str;

	branch = 0;
	while (stree->branches && branch < stree->num_branches && stree->type == REDIRECTION)
	{
		if (stree->branches[branch]->type == HEREDOC_DELIMITER || stree->branches[branch]->type == HEREDOC_QUOTED_DELIMITER)
			perform_heredoc(revert_transform(stree->branches[branch]->value), ms_vars, stree->branches[branch]->type);
		branch++;
	}
	branch = 0;
	while (branch < stree->num_branches)
	{
		if (stree->branches[branch]->type == WORD)
		{
			expanded_str = perform_parameter_expansions(stree->branches[branch]->value, ms_vars);
			if (!expanded_str)
				error_cleanup(ms_vars);
			expanded_str = perform_wildcard_expansions(expanded_str);
			if (!expanded_str)
				error_cleanup(ms_vars);
			get_exec_args(expanded_str, ms_vars);
		}
		else if (stree->branches[branch]->type == T_FILE)
		{
			expanded_str = perform_parameter_expansions(stree->branches[branch]->value, ms_vars);
			if (!expanded_str)
				error_cleanup(ms_vars);
			expanded_str = perform_wildcard_expansions(expanded_str);
			if (!expanded_str)
				error_cleanup(ms_vars);
			check_ambigious_redirections(expanded_str, ms_vars);
			perform_redirection(revert_transform(expanded_str), ms_vars);
		}
		else if (stree->branches[branch]->type == HEREDOC_DELIMITER || stree->branches[branch]->type == HEREDOC_QUOTED_DELIMITER)
			perform_redirection(revert_transform(stree->branches[branch]->value), ms_vars);
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
	if (ms_vars->exec_argv[0])
		exec_cmd(ms_vars);
}

void	parse_tree(t_syntax_tree *stree, t_ms_vars *ms_vars)
{
	int		branch;
	pid_t	pid;
	int		i;
	int		status;

	branch = 0;
	i = 0;
	if (stree->type == PIPE)
	{
		if (stree->num_branches > 1)
		{
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
					parse_cmd_redirects(stree->branches[branch], ms_vars);
					error_cleanup(ms_vars);
					exit(EXIT_SUCCESS);
				}
				ms_vars->pid_arr[i++] = pid;
				branch++;
			}
			i = 0;
			while (ms_vars->pid_arr[i] != 0)
			{
				waitpid(ms_vars->pid_arr[i], &status, 0);
				if (WIFEXITED(status))
					ms_vars->exit_value = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					ms_vars->exit_value = 128 + WTERMSIG(status);
				i++;
			}
		}
		else
		{
			/*todo: if command is a builtin, execute as per normal, otherwise 
			fork a child process and do execve*/
			return ;
		}
	}
	while (stree->branches && branch < stree->num_branches && stree->type != PIPE)
	{
		parse_tree(stree->branches[branch], ms_vars);
		branch++;
	}
}
