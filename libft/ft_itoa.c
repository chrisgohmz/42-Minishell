/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:46:46 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 15:25:52 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *str, int negative, unsigned int num, int len)
{
	int		i;

	str[len] = '\0';
	i = len - 1;
	while (i >= negative)
	{
		str[i] = '0' + num % 10;
		num /= 10;
		i--;
	}
	if (negative)
		str[0] = '-';
}

static int	count_length(unsigned int n)
{
	int		len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	int				negative;
	unsigned int	num;
	char			*str;

	if (n < 0)
	{
		negative = 1;
		num = (unsigned int) -n;
	}
	else
	{
		negative = 0;
		num = (unsigned int) n;
	}
	len = count_length(num) + negative;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	fill_str(str, negative, num, len);
	return (str);
}
