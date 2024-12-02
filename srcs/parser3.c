/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:59:25 by cgoh              #+#    #+#             */
/*   Updated: 2024/12/03 02:05:05 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disable_value_word_splitting(char *str)
{
	int		i;
	bool	disable;
	
	i = 0;
	disable = false;
	while (str[i])
	{
		if (str[i] == '=')
			disable = true;
		else if (disable && str[i] == '$')
			str[i] = DQUOTE_DOLLAR;
		else if (disable && str[i] == '*')
			str[i] = ESC_WILDCARD;
		i++;
	}
}
