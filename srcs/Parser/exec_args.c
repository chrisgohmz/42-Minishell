/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:08:41 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/04 18:44:52 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	get_exec_args(char **split_arr, t_ms_vars *ms_vars)
{
	int		num_elements;

	num_elements = count_split_elements(split_arr);
	if (num_elements > 0)
	{
		ms_vars->exec_argv = ft_realloc_str_arr(ms_vars->exec_argv,
				ms_vars->argv_index + num_elements + 1);
		if (!ms_vars->exec_argv)
		{
			free_2d_arr((void ***)&split_arr);
			exit_cleanup(ms_vars);
		}
		add_to_argv(split_arr, ms_vars);
	}
}
