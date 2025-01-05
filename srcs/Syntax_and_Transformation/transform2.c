/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:25:24 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/05 23:26:15 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	revert_wildcard_transform(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == WILDCARD)
			str[i] = '*';
	}
}
