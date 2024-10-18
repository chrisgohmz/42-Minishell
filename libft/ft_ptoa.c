/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:12 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/25 20:27:34 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *addr_str, unsigned long addr_l, int index, char *hex)
{
	if (addr_l == 0)
		return ;
	fill_str(addr_str, addr_l / 16, index - 1, hex);
	addr_str[index] = hex[addr_l % 16];
}

static int	get_len(unsigned long addr_l)
{
	int		i;

	i = 1;
	addr_l /= 16;
	while (addr_l)
	{
		addr_l /= 16;
		i++;
	}
	return (i);
}

char	*ft_ptoa(void *ptr)
{
	unsigned long	addr_l;
	char			*addr_str;
	char			*hex;
	int				len;

	addr_l = (unsigned long)ptr;
	if (!addr_l)
		return (ft_strdup("(nil)"));
	len = get_len(addr_l);
	addr_str = malloc((len + 1) * sizeof(char));
	if (!addr_str)
		return (NULL);
	hex = "0123456789abcdef";
	fill_str(addr_str, addr_l, len - 1, hex);
	addr_str[len] = '\0';
	return (addr_str);
}
