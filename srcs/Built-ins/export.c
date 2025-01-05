/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:27 by lpwi              #+#    #+#             */
/*   Updated: 2025/01/05 15:09:11 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_valid_key_value(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i])
	{
		if (str[i] == '=')
			return (1);
		return (0);
	}
	return (2);
}

static int	ft_new_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

static int	var_index(int env_size, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = ft_new_strlen(var);
	while (i < env_size)
	{
		if (ft_strncmp(var, environ[i], j) == 0)
		{
			if (environ[i][j] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	process_args(t_ms_vars *ms_vars, int i, int err)
{
	int	is_valid_key;
	int	v_index;

	is_valid_key = ft_valid_key_value(ms_vars->exec_argv[i]);
	if (!is_valid_key)
	{
		ft_dprintf(STDERR_FILENO, "export: %s: not a valid identifier\n",
			ms_vars->exec_argv[i]);
		err = 1;
	}
	else if (is_valid_key == 1)
	{
		v_index = var_index(ms_vars->env_size, ms_vars->exec_argv[i]);
		if (v_index == -1)
		{
			ms_vars->ep[ms_vars->env_size] = ft_strdup(ms_vars->exec_argv[i]);
			(ms_vars->env_size)++;
		}
		else
		{
			free(ms_vars->ep[v_index]);
			ms_vars->ep[v_index] = ft_strdup(ms_vars->exec_argv[i]);
		}
	}
	return (err);
}

void	export_builtin(t_ms_vars *ms_vars)
{
	int	i;
	int	new_vars_count;
	int	err;

	i = 1;
	err = 0;
	new_vars_count = 0;
	while (ms_vars->exec_argv[i])
	{
		if (ft_valid_key_value(ms_vars->exec_argv[i]) == 1
			&& var_index(ms_vars->env_size, ms_vars->exec_argv[i]) == -1)
			new_vars_count++;
		i++;
	}
	if (new_vars_count)
		ms_vars->ep = ft_realloc_str_arr(ms_vars->ep,
				new_vars_count + ms_vars->env_size + 1);
	environ = ms_vars->ep;
	i = 1;
	while (ms_vars->exec_argv[i])
	{
		err = process_args(ms_vars, i, err);
		i++;
	}
	ms_vars->exit_value = err;
}
