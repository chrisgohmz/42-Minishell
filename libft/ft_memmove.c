/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:21:41 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 17:53:03 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*d;
	void	*s;

	d = NULL;
	s = NULL;
	if (dest == src)
		return (dest);
	if (src < dest && dest - src < (int)n)
	{
		d = dest + n - 1;
		s = (void *)src + n - 1;
		while (n--)
			*((unsigned char *)d--) = *((unsigned char *)s--);
	}
	else
	{
		d = dest;
		s = (void *)src;
		while (n--)
			*((unsigned char *)d++) = *((unsigned char *)s++);
	}
	return (dest);
}
