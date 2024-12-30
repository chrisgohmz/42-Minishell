/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpwi <lpwi@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:59:16 by lpwi              #+#    #+#             */
/*   Updated: 2024/12/14 18:28:52 by lpwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ctrl C (SIGINT) - return prompt
    ctrl D - exit shell
    ctrl \ - do nothing

    Ign: Ignore the signal; i.e., do nothing, just return
    Term: terminate the process
    Cont: unblock a stopped process
    Stop: block the process
*/

void sigint_handler(int)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_sigint = 1;
}

void    minishell_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    g_sigint = 0;
}
