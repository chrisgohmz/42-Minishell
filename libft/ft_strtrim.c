/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:14:14 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 22:03:52 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *trimmed, char const *s1, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		trimmed[i] = s1[start];
		start++;
		i++;
	}
	trimmed[i] = '\0';
}

static int	find_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static int	find_end(char const *s1, char const *set, int end)
{
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		end;
	int		size;
	char	*trimmed;

	len = 0;
	while (s1[len])
		len++;
	start = find_start(s1, set);
	end = find_end(s1, set, len - 1);
	if (start > end)
		size = 1;
	else
		size = end - start + 2;
	trimmed = malloc(size * sizeof(char));
	if (!trimmed)
		return (NULL);
	fill_str(trimmed, s1, start, end);
	return (trimmed);
}
