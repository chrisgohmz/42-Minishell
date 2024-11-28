/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:22:39 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 03:52:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *restrict str1, const char *restrict str2, size_t n)
{
	size_t			i;
	unsigned char	*u_str1;
	unsigned char	*u_str2;

	if (n == 0)
		return (0);
	u_str1 = (unsigned char *)str1;
	u_str2 = (unsigned char *)str2;
	i = 0;
	while (u_str1[i] && u_str2[i] && u_str1[i] == u_str2[i] && i < n - 1)
		i++;
	return (u_str1[i] - u_str2[i]);
}
