/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:56:44 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 15:30:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*((unsigned char *)str1 + i) == *((unsigned char *)str2 + i)
		&& i < n - 1)
		i++;
	return (*((unsigned char *)str1 + i) - *((unsigned char *)str2 + i));
}
