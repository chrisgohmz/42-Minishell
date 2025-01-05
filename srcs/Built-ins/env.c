/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:11 by lpwi              #+#    #+#             */
/*   Updated: 2025/01/05 15:07:15 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_builtin(t_ms_vars *ms_vars)
{
	int	i;

	i = 0;
	while (ms_vars->ep[i])
	{
		ft_putendl_fd(ms_vars->ep[i], STDOUT_FILENO);
		i++;
	}
	ms_vars->exit_value = EXIT_SUCCESS;
}
