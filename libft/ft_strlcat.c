/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:00:42 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 22:01:22 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_n;
	size_t	dest_len;

	src_n = 0;
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while (src_n < size - 1 - dest_len && src[src_n])
	{
		dest[dest_len + src_n] = src[src_n];
		src_n++;
	}
	dest[dest_len + src_n] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[src_n]));
}
