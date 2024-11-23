/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:27 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:42:39 by cgoh             ###   ########.fr       */
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
Infinite loop when running export command.
ms_vars->env_size contains the number of entries in env, so don't need to recalculate env_size again.
Remember to account for the +1 size required for the NULL pointer when passing new_size to ft_realloc_str_arr.
*/

// static int	arr_size(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while(arr[i])
// 		i++;
// 	return(i);
// }

static bool	ft_valid_key_value(char *str)
{
	int	i;

	i = 0;
	while(ft_isalnum(str[i]))
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

static int	var_index(char *var)
{
	int	i;
	int	j;

	i = 0;
	j = ft_new_strlen(var);
	while(__environ[i])
	{
		if(ft_strncmp(var, __environ[i], j) == 0)
		{
			if(__environ[i][j] == '=')
			{
				// printf("i is %i\n", i);
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

void	export_builtin(t_ms_vars *ms_vars)
{
	int	i;
	int	j;
	char	**temp;
	int	new_vars_count;

	i = 1;
	new_vars_count = 0;
	while (ms_vars->exec_argv[i])
	{
		if(!ft_valid_key_value(ms_vars->exec_argv[i]))
			i++;
		else if(var_index(ms_vars->exec_argv[i]) == -1)
		{
			new_vars_count++;
			i++;
		}
		else
			i++;
	}
	printf("var count %i\n", new_vars_count);
	j = ms_vars->env_size;
	printf("j %i\n", j);
	temp = ft_realloc_str_arr(ms_vars->ep, new_vars_count + j + 1);
	i = 1;
	while(ms_vars->exec_argv[i])
	{
		if(!ft_valid_key_value(ms_vars->exec_argv[i]))
			printf("'%s': invalid", ms_vars->exec_argv[i]);
		else if(var_index(ms_vars->exec_argv[i]) == -1)
		{
			temp[j] = ft_strdup(ms_vars->exec_argv[i]);
			j++;
		}
		else
			ft_strlcpy(temp[var_index(ms_vars->exec_argv[i])], ms_vars->exec_argv[i], ft_strlen(ms_vars->exec_argv[i]));
		i++;
	}
	temp[j] = NULL;
	__environ = temp;
}
