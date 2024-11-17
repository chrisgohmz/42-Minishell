/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:27 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 14:36:28 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** export **/
/* make environment variable (from a shell variable) available to child processes. allow updates and propagation of the environment variable values to the current shell session and any spawned child processes. ensure that changes are immediately effective.
   display all exported variables.
   handle path and any new variable. */

/* loop through exec_argv[1] onwards to identify the __envrion variables to change */
/* in each loop, look for = (key=value), if key exists in environ, overwite the value with value otherwise add key=value pair to __environ. */
/* store each key-value pair as an array */
/* size_t size should consider variables that already exists in environ */
/* use ft_alloc_str_arr to create a new and bigger array to store all environ vars and the new vars. then redefine __environ to the new array */

int	arr_size(char **arr)
{
	int	i;
	
	i = 0;
	while(arr[i])
		i++;
	return(i);
}

bool	ft_valid_key_value(char *str)
{
	int	i;

	i = 0;
	while(ft_isalnum(str[i]))
		i++;
	while(str[i] == '=')
		return (TRUE);
	return(FALSE);
}

int	var_index(char *var)
{
	int	i;
	int	j;

	i = 0;
	while(__environ[i])
	{
		j = 0;
		while(var[j] != '=')
		{
			if(__environ[i][j] == var[j])
				j++;
		}
		if(__environ[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_export(char **exec_argv)
{
	int	i;
	int	j;
	char	**temp;
	int	new_vars_count;

	i = 1;
	new_vars_count = 0;
	while (exec_argv[i])
	{
		if(!ft_valid_key_value(exec_argv[i]))
			i++;
		else if(var_index(exec_argv[i]) == -1)
		{
			new_vars_count++;
			i++;
		}
	}
	j = arr_size(__environ);
	temp = ft_realloc_str_arr(__environ, new_vars_count + j);
	i = 1;
	while(exec_argv[i])
	{
		if(!ft_valid_key_value(exec_argv[i]))
			printf("'%s': invalid", exec_argv[i]);
		else if(var_index(exec_argv[i]) == -1)
		{
			temp[j] = ft_strdup(exec_argv[i]);
			j++;
		}
		else
			ft_strlcpy(temp[var_index(exec_argv[i])], exec_argv[i], ft_strlen(exec_argv[i]));
		i++;
	}
	__environ = temp;

}	


