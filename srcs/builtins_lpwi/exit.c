/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:22 by lpwi              #+#    #+#             */
/*   Updated: 2024/11/17 21:46:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/** exit **/
/* exit the current shell session.
   take no options: returns the exit status of the last command. */

/*
1 more case to handle: exit with non-numeric argument (e.g exit blah)
Invalid read when exit with no arguments is called.
exit with no arguments should exit the shell with the last saved exit value.
*/
void	exit_builtin(t_ms_vars *ms_vars)
{
   int   exit;
   if(ms_vars->exec_argv[2])
   {
      ms_vars->exit_value = 1;
      printf("exit\nexit: too many arguments\n");
      return ;
   }
   if(ms_vars->exec_argv[1])
   {
      exit = ft_atoi(ms_vars->exec_argv[1]);
      ms_vars->exit_value = exit;
   }
   else
      ms_vars->exit_value = 0;
   printf("exit\n");
	error_cleanup(ms_vars);
}
