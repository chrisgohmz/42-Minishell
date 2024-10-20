/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:09:38 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/20 21:09:46 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_static_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = (void *)0x1;
		i++;
	}
}

char	*find_key_value(char *env, char *key)
{
	while (*env && *key && *env == *key)
	{
		env++;
		key++;
	}
	if (*env == '=' && (!*key || (!ft_isalnum(*key) && *key != '_')))
		return (++env);
	return (NULL);
}

char	*find_env_value(char **new_envp, char *key)
{
	int		i;
	char	*value;

	i = 0;
	key++;
	while (new_envp[i])
	{
		value = find_key_value(new_envp[i], key);
		if (value)
			return (value);
		i++;
	}
	return ("\0");
}

int	make_new_envp(char **new_envp, char **envp)
{
	int		i;
	size_t	env_len;

	i = 0;
	while (envp[i])
	{
		env_len = ft_strlen(envp[i]);
		new_envp[i] = ft_calloc(env_len + 1, sizeof(char));
		if (!new_envp[i])
		{
			printf("Malloc failed for new_envp\n");
			free_2d_static_arr(new_envp);
			return (0);
		}
		ft_strlcpy(new_envp[i], envp[i], env_len + 1);
		i++;
	}
	new_envp[i] = NULL;
	return (1);
}
