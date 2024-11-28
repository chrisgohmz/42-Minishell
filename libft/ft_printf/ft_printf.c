/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:00:19 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:28:38 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

static int	get_length(va_list va_ptr, const char *format, t_format *format_lst)
{
	int		i;
	int		len;
	int		str_len;

	i = 0;
	len = 0;
	while (format[i])
	{
		str_len = parse_str(va_ptr, &i, format, format_lst);
		if (str_len == -1)
		{
			len = -1;
			break ;
		}
		len += str_len;
		i++;
	}
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int			len;
	va_list		va_ptr;
	t_format	format_lst;

	va_start(va_ptr, format);
	format_lst.fd = fd;
	len = get_length(va_ptr, format, &format_lst);
	va_end(va_ptr);
	return (len);
}
