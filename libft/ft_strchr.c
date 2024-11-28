/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:47:10 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 03:42:17 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *restrict str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)str + i);
	return (NULL);
}
