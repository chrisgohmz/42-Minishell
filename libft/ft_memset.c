/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:58:40 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 03:38:22 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *restrict str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ustr;

	ustr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		ustr[i] = c;
		i++;
	}
	return (str);
}
