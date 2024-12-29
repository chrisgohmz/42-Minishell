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
   if(str[i] == '-' || str[i] == '+')
      i++;
   while(str[i])
   {
      if(ft_isdigit(str[i]) == 0)
         return (1);
      i++;
   }
   return (0);
}

int check_value(char *str)
{
   int sign;
   int i;
   int len;
   char *max = "2147483647";

   i = 0;
   if(str[i] == '+' || str[i] == '-')
   {
      if(str[i] == '+')
         sign = 1;
      else if(str[i] == '-')
         sign = -1;
      i++;
   }
   len = ft_strlen(&str[i]);
   if(len > 10)
      return (1);
   else if(len == 10 && ft_strncmp(max, &str[i], len) < 0)
      return (1);
   else
      return (0);
}

void	exit_builtin(t_ms_vars *ms_vars)
{
   ft_putendl_fd("exit", STDOUT_FILENO);
   if(ms_vars->exec_argv[1])
   {
      if(non_numeric_string(ms_vars->exec_argv[1]) == 1)
      {   
         ms_vars->exit_value = 2;
         ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
         exit_cleanup(ms_vars);
         return ;
      }
      else if(ms_vars->exec_argv[2])
      {
         ms_vars->exit_value = 1;
         ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
         return ;
      }
      if(check_value(ms_vars->exec_argv[1]) == 1)
      {   
         ms_vars->exit_value = 2;
         ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
         exit_cleanup(ms_vars);
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