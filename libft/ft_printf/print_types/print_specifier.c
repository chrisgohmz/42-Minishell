/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:55:58 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/03 04:00:56 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_specifier(const char *format, int start, int end,
	t_format *format_lst)
{
	int		len;

	ft_putchar_fd('%', format_lst->fd);
	len = end - start + 1;
	while (start <= end)
		ft_putchar_fd(format[start++], format_lst->fd);
	return (len + 1);
}
