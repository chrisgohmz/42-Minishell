/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:02:03 by cgoh              #+#    #+#             */
/*   Updated: 2024/07/08 20:10:06 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	valid_base(char *base)
{
	size_t	i;

	i = 0;
	if (ft_strlen(base) <= 1)
		return (0);
	while (i < ft_strlen(base) && base[i] != '+' && base[i] != '-'
		&& base[i] != base[i + 1] && !(base[i] >= '\t'
			&& base[i] <= '\r') && base[i] != ' ')
	{
		i++;
	}
	return (base[i] == '\0');
}

int	valid_char(char c, char *base)
{
	int	n;

	n = 1;
	while (base[n - 1] != '\0')
	{
		if (c == base[n - 1])
			return (n);
		n++;
	}
	return (0);
}

int	convert(char *str, char *base)
{
	int	result;
	int	base_t;
	int	n;
	int	multiplier;

	result = 0;
	base_t = ft_strlen(base);
	n = 0;
	multiplier = 1;
	while (valid_char(*(str + n), base))
	{
		n++;
	}
	n--;
	while (n >= 0)
	{
		result += (valid_char(*(str + n), base) - 1) * multiplier;
		multiplier *= base_t;
		n--;
	}
	return (result);
}

int	ft_atoi_base(char *str, char *base)
{
	int	c;
	int	s;

	c = 0;
	s = 1;
	if (!valid_base(base))
		return (0);
	while ((str[c] >= '\t' && str[c] <= '\r') || str[c] == ' ')
		c++;
	while (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	return (convert(str + c, base) * s);
}
