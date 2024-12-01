/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:04:08 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/02 01:34:18 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_exit_value(unsigned char exit_value, char *new_str, int *j)
{
	if (exit_value == 0)
		return ;
	insert_exit_value(exit_value / 10, new_str, j);
	new_str[(*j)++] = exit_value % 10 + '0';
}
