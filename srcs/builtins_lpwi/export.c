/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:27 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/24 01:59:38 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** export **/
/* make environment variable (from a shell variable) available to child processes. allow updates and propagation of the environment variable values to the current shell session and any spawned child processes. ensure that changes are immediately effective.
   display all exported variables.
   handle path and any new variable. */

/* loop through ms_vars->exec_argv[1] onwards to identify the __envrion variables to change */
/* in each loop, look for = (key=value), if key exists in environ, overwite the value with value otherwise add key=value pair to __environ. */
/* store each key-value pair as an array */
/* size_t size should consider variables that already exists in environ */
/* use ft_alloc_str_arr to create a new and bigger array to store all environ vars and the new vars. then redefine __environ to the new array */

/*
Not able to export a variable with _ in it.
The rule for an identifier is:
1. first character must be alphabet or _
2. Second character onwards must be alphanumeric or _
Exporting an existing variable with a longer length than the current one results in invalid write.
Hint: Does ft_strlcpy work when the array size is different?
*/

static bool	ft_valid_key_value(char *str)
{
	int	i;

	i = 0;
	if(ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return (false);
	while(ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=')
		return (true);
	return(false);
}

static int ft_new_strlen(char *str)
{
	int i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

static int	var_index(int env_size, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = ft_new_strlen(var);
	while(i < env_size)
	{
		if(ft_strncmp(var, __environ[i], j) == 0)
		{
			if(__environ[i][j] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	export_builtin(t_ms_vars *ms_vars)
{
	int	i;
	int	j;
	int	new_vars_count;
	int	err;

	i = 1;
	new_vars_count = 0;
	err = 0;
	while (ms_vars->exec_argv[i])
	{
		if(ft_valid_key_value(ms_vars->exec_argv[i]) && var_index(ms_vars->env_size, ms_vars->exec_argv[i]) == -1)
			new_vars_count++;
		i++;
	}
	j = ms_vars->env_size;
	ms_vars->ep = ft_realloc_str_arr(ms_vars->ep, new_vars_count + j + 1);
	__environ = ms_vars->ep;
	i = 1;
	while(ms_vars->exec_argv[i])
	{
		if(!ft_valid_key_value(ms_vars->exec_argv[i]))
		{
			ft_dprintf(STDERR_FILENO, "\e[1;91mexport: %s: not a valid identifier\n\e[1;91m", ms_vars->exec_argv[i]);
			err = 1;
		}
		else if(var_index(ms_vars->env_size, ms_vars->exec_argv[i]) == -1)
		{
			ms_vars->ep[j] = ft_strdup(ms_vars->exec_argv[i]);
			j++;
		}
		else
			ms_vars->ep[var_index(ms_vars->env_size, ms_vars->exec_argv[i])] = ft_strdup(ms_vars->exec_argv[i]);
		i++;
	}
	ms_vars->env_size = j;
	ms_vars->exit_value = err;
}
