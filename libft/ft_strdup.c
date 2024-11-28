/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:26:28 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 03:43:25 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *restrict str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, len + 1);
	return (dup);
}
