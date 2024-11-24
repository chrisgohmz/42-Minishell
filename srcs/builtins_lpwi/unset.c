/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:42 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:47:02 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** unset **/
/* undefine a variable during the program execution. */

/*
lpwi - export A B C D. unset A ok. unset D after causes segfault. to check again.
*/

static int	key_len(char *key)
{
	int i;

	i = 0;
	while(key[i] != '=')
		i++;
	return (i);
}

static int	find_unset_pos(t_ms_vars *ms_vars, char *key)
{
	unsigned int i;

	i = 0;
	while(key[i])
	{
		if(key[i] == '=')
			return (-1);
		i++;
	}
	i = 0;
	while (i < ms_vars->env_size)
	{
		if(ft_strncmp(ms_vars->ep[i], key, key_len(ms_vars->ep[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	free_old_ep(char **temp)
{
	int i;

	i = 0;
	while(temp[i])
		i++;
	i--;
	while(i >= 0)
	{
		free(temp[i]);
		i--;
	}
	free(temp);		
}

static int to_keep(t_ms_vars *ms_vars, int index)
{
	int i;

	i = 1;
	while (ms_vars->exec_argv[i])
	{
		if(find_unset_pos(ms_vars, ms_vars->exec_argv[i]) == index)
			return (0);
		i++;
	}
	return (1);
}

static void copy_invalid_keys(t_ms_vars *ms_vars, char **new_ep)
{
	int i;
	int k;
	int pos;

	i = 0;
	k = 0;
	pos = -1;
	while (ms_vars->ep[i])
	{
		if(to_keep(ms_vars, i))
		{
			new_ep[k] = ft_strdup(ms_vars->ep[i]);
			k++;
		}
		i++;
	}
}

void	unset_builtin(t_ms_vars *ms_vars)
{
	int i;
	char **new_ep;
	char **temp;

	i = 1;
	while (ms_vars->exec_argv[i])
	{
		if(find_unset_pos(ms_vars, ms_vars->exec_argv[i]) >= 0)
			(ms_vars->env_size)--;
		i++;
	}
	new_ep = malloc(sizeof(char *) * (ms_vars->env_size + 1));
	if (!new_ep)
		printf("unsuccessful malloc\n");
	copy_invalid_keys(ms_vars, new_ep);
	temp = ms_vars->ep;
	ms_vars->ep = new_ep;
	free_old_ep(temp);
	__environ = ms_vars->ep;
}
