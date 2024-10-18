/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:02:18 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 15:25:32 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*mem;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		*((unsigned char *)mem + i) = 0;
		i++;
	}
	return (mem);
}
