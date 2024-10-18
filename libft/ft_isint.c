/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:53:33 by cgoh              #+#    #+#             */
/*   Updated: 2024/06/10 20:59:35 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_limits(char *str)
{
	size_t	negative;

	negative = (str[0] == '-');
	if (ft_strlen(str) > 10 + negative)
		return (0);
	else if (ft_strlen(str) == 10 + negative)
	{
		if (negative && (ft_strncmp(str, "-2147483648", 11) > 0))
			return (0);
		else if (!negative && (ft_strncmp(str, "2147483647", 10) > 0))
			return (0);
	}
	return (1);
}

int	ft_isint(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (check_limits(str));
}
