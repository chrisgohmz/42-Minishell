/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:53:31 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 21:07:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_ambiguous_redirections(char **split_arr, char *str)
{
	int	i;

	i = 0;
	while (split_arr[i] && i < 2)
		i++;
	if (i != 1)
	{
		ft_dprintf(STDERR_FILENO, "\e[1;91mError: %s: ambiguous redirect"
			"\e[0m\n", revert_transform(str));
		return (1);
	}
	return (0);
}

static char	**do_expansions(char *str, t_ms_vars *ms_vars)
{
	char	*expanded_str;
	char	**split_arr;

	expanded_str = perform_parameter_expansions(str, ms_vars);
	if (!expanded_str)
		return (NULL);
	expanded_str = remove_quotes_in_non_null_args(expanded_str);
	if (!expanded_str)
		return (NULL);
	split_arr = perform_wildcard_expansions(expanded_str);
	if (!split_arr)
		return (NULL);
	return (split_arr);
}

void	handle_heredoc_token(char **value, t_ms_vars *ms_vars)
{
	if (!perform_redirection(value, ms_vars))
	{
		ms_vars->exit_value = EXIT_FAILURE;
		if (ms_vars->proc_type == CHILD)
			exit_cleanup(ms_vars);
		else
			return (free_2d_arr((void ***)&ms_vars->exec_argv));
	}
}

void	handle_file_token(char *value, t_ms_vars *ms_vars)
{
	char	**split_arr;

	split_arr = do_expansions(value, ms_vars);
	if (!split_arr)
		exit_cleanup(ms_vars);
	if (check_ambiguous_redirections(split_arr, value)
		|| !perform_redirection(&split_arr[0], ms_vars))
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

void	handle_word_token(char *value, t_ms_vars *ms_vars)
{
	char	**split_arr;

	split_arr = do_expansions(value, ms_vars);
	if (!split_arr)
		exit_cleanup(ms_vars);
	get_exec_args(split_arr, ms_vars);
	free(split_arr);
	split_arr = NULL;
}