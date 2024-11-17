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

char	*ft_getenv(const char *name)
{
	char	*env;
	char	*key;
	char	*key_end;

	key = NULL;
	key_end = (char *)name;
	while (ft_isalnum(*key_end) || *key_end == '_')
		key_end++;
	if (*key_end)
	{
		key = ft_substr(name, 0, key_end - name);
		if (!key)
			return (NULL);
		env = getenv(key);
	}
	else
		env = getenv(name);
	free(key);
	if (!env)
		return ("\0");
	return (env);
}

int	make_new_envp(t_ms_vars *ms_vars)
{
	size_t	size;
	size_t	env_len;

	size = 0;
	while (__environ[size])
		size++;
	ms_vars->ep = ft_calloc(size + 1, sizeof(char *));
	if (!ms_vars->ep)
		return (0);
	size = 0;
	while (__environ[size])
	{
		env_len = ft_strlen(__environ[size]);
		ms_vars->ep[size] = malloc((env_len + 1) * sizeof(char));
		if (!ms_vars->ep[size])
			return (free_2d_malloc_array(&ms_vars->ep), 0);
		ft_strlcpy(ms_vars->ep[size], __environ[size], env_len + 1);
		size++;
	}
	__environ = ms_vars->ep;
	return (1);
}
