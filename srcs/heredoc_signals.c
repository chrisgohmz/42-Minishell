/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:34:10 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/24 14:42:13 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int rl_event_handler(void)
{
	return (1);
}

void heredoc_sigint_handler(int)
{
	g_sigint = 1;
    rl_done = true;
}
