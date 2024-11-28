/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:39:08 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:30:43 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*malloc_str_u(unsigned int n, int precision)
{
	int		len;
	char	*n_str;
	char	*formatted_u;

	n_str = ft_utoa(n);
	if (!n_str)
		return (NULL);
	len = ft_strlen(n_str) - (n == 0 && precision == 0);
	if (precision > len)
		len = precision;
	free(n_str);
	formatted_u = malloc((len + 1) * sizeof(char));
	if (!formatted_u)
		return (NULL);
	ft_memset(formatted_u, 1, len);
	formatted_u[len] = '\0';
	return (formatted_u);
}

static int	fill_formatted_u(char *formatted_u, unsigned int n)
{
	char	*n_str;
	int		i;
	int		n_start;

	n_str = ft_utoa(n);
	if (!n_str)
		return (0);
	i = 0;
	n_start = ft_strlen(formatted_u) - ft_strlen(n_str);
	while (i < n_start)
		formatted_u[i++] = '0';
	formatted_u[i] = '\0';
	ft_strlcat(formatted_u, n_str, n_start + ft_strlen(n_str) + 1);
	free(n_str);
	return (1);
}

static void	print_formatted_u(char *formatted_u, t_format *format_lst)
{
	int		left;
	char	*flags;
	int		width;

	left = 0;
	flags = format_lst->flags;
	width = format_lst->width;
	if (ft_strchr(flags, '-'))
		left = 1;
	while (!left && width-- > (int)ft_strlen(formatted_u))
	{
		if (format_lst->precision < 0 && ft_strchr(flags, '0'))
			ft_putchar_fd('0', format_lst->fd);
		else
			ft_putchar_fd(' ', format_lst->fd);
	}
	ft_putstr_fd(formatted_u, format_lst->fd);
	while (width-- > (int)ft_strlen(formatted_u))
		ft_putchar_fd(' ', format_lst->fd);
}

int	print_u(t_format *format_lst, unsigned int n)
{
	char	*formatted_u;
	int		len;

	formatted_u = malloc_str_u(n, format_lst->precision);
	if (!formatted_u)
		return (-1);
	if (!fill_formatted_u(formatted_u, n))
		return (-1);
	print_formatted_u(formatted_u, format_lst);
	if (format_lst->width > (int)ft_strlen(formatted_u))
		len = format_lst->width;
	else
		len = ft_strlen(formatted_u);
	free(formatted_u);
	return (len);
}
