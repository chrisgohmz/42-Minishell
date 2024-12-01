/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:59:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/02 02:05:23 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disable_value_word_splitting(char *str)
{
	int	i;
	int	disable;

	i = 0;
	disable = 0;
	while (str[i])
	{
		if (str[i] == '=')
			disable = 1;
		else if (disable && str[i] == '$')
			str[i] = DQUOTE_DOLLAR;
		else if (disable && str[i] == '*')
			str[i] = ESC_WILDCARD;
		i++;
	}
}
