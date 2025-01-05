/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:42 by lpwi              #+#    #+#             */
/*   Updated: 2025/01/05 15:19:27 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cmp_len(char *key, char *ep_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (key[i])
		i++;
	while (ep_var[j] != '=')
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}

static int	find_unset_pos(t_ms_vars *ms_vars, char *key)
{
	unsigned int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			return (-1);
		i++;
	}
	i = 0;
	while (i < ms_vars->env_size)
	{
		if (ft_strncmp(ms_vars->ep[i], key, cmp_len(key, ms_vars->ep[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	to_keep(t_ms_vars *ms_vars, int index)
{
	int	i;

	i = 1;
	while (ms_vars->exec_argv[i])
	{
		if (find_unset_pos(ms_vars, ms_vars->exec_argv[i]) == index)
			return (0);
		i++;
	}
	return (1);
}

static void	copy_invalid_keys(t_ms_vars *ms_vars, char **new_ep)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (ms_vars->ep[i])
	{
		if (to_keep(ms_vars, i))
		{
			new_ep[k] = ft_strdup(ms_vars->ep[i]);
			k++;
		}
		i++;
	}
}

void	unset_builtin(t_ms_vars *ms_vars)
{
	int		i;
	char	**new_ep;
	char	**temp;
	int		new_size;

	i = 1;
	new_size = ms_vars->env_size;
	while (ms_vars->exec_argv[i])
	{
		if (find_unset_pos(ms_vars, ms_vars->exec_argv[i]) >= 0)
			new_size--;
		i++;
	}
	new_ep = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_ep)
		printf("unsuccessful malloc\n");
	copy_invalid_keys(ms_vars, new_ep);
	temp = ms_vars->ep;
	ms_vars->ep = new_ep;
	free_2d_arr((void ***)&temp);
	environ = ms_vars->ep;
	ms_vars->env_size = new_size;
	ms_vars->exit_value = EXIT_SUCCESS;
}
