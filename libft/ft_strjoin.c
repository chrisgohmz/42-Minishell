/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:57:37 by cgoh              #+#    #+#             */
/*   Updated: 2024/07/04 18:12:45 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcat(char *str, char const *cat, int *j)
{
	int	i;

	i = 0;
	while (cat[i])
	{
		str[*j] = cat[i];
		i++;
		(*j)++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		j;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(len * sizeof(char));
	if (!joined)
		return (NULL);
	j = 0;
	ft_strcat(joined, s1, &j);
	ft_strcat(joined, s2, &j);
	joined[j] = '\0';
	return (joined);
}
