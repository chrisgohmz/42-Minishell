/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:09:38 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/17 18:11:46 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name)
{
	char	*env;
	char	*key_end;
	char	save_char;

	key_end = name;
	while (ft_isalnum(*key_end) || *key_end == '_')
		key_end++;
	if (*key_end)
	{
		save_char = *key_end;
		*key_end = '\0';
		env = getenv(name);
		*key_end = save_char;
	}
	else
		env = getenv(name);
	if (!env)
		return ("\0");
	return (env);
}

int	make_new_envp(t_ms_vars *ms_vars)
{
	ms_vars->env_size = 0;
	while (__environ[ms_vars->env_size])
		ms_vars->env_size++;
	ms_vars->ep = ft_calloc(ms_vars->env_size + 1, sizeof(char *));
	if (!ms_vars->ep)
		return (0);
	ms_vars->env_size = 0;
	while (__environ[ms_vars->env_size])
	{
		ms_vars->ep[ms_vars->env_size] = ft_strdup(__environ[ms_vars->env_size]);
		if (!ms_vars->ep[ms_vars->env_size])
			return (free_2d_malloc_array(&ms_vars->ep), 0);
		ms_vars->env_size++;
	}
	__environ = ms_vars->ep;
	return (1);
}
