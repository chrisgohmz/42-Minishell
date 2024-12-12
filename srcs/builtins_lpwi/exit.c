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

int   non_numeric_string(char *str)
{
   int   i;

   i = 0;
   while(str[i])
   {
      if(ft_isdigit(str[i]) == 0)
         return (1);
      i++;
   }
   return (0);
}

void	exit_builtin(t_ms_vars *ms_vars)
{
   printf("exit\n");
   if(ms_vars->exec_argv[1])
   {
      if(non_numeric_string(ms_vars->exec_argv[1]) == 1)
      {   
         ms_vars->exit_value = 2;
         if(non_numeric_string(ms_vars->exec_argv[1]) == 1)
            perror("exit: numeric argument required\n");
         exit_cleanup(ms_vars);
      }
      else if(ms_vars->exec_argv[2])
      {
         ms_vars->exit_value = 1;
         perror("exit: too many arguments\n");
         return ;
      }
      else
      {
         ms_vars->exit_value = ft_atoi(ms_vars->exec_argv[1]);
         exit_cleanup(ms_vars);
      }
   }
   else
      exit_cleanup(ms_vars);
}
/*
if arg[1] exists:
if arg[1] is not numeric, exit with exit error.
else: check for multiple args
   if there are multiple args: do not exit and display error
   else: exit normally.
*/