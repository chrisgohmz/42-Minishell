/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:34 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:31:41 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** pwd **/
/* take no options.
   output the current path, terminated with a newline. */

/*
Check for error return from getcwd().
*/
void	pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	if(getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
}
