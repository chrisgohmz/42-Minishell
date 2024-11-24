/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:07:26 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/23 12:02:31 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	size_t	i;
	char	*udest;
	char	*usrc;

	i = 0;
	udest = (char *)dest;
	usrc = (char *)src;
	while (i < n)
	{
		udest[i] = usrc[i];
		i++;
	}
	return (dest);
}
