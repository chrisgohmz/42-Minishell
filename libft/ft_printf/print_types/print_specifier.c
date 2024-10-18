/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:55:58 by cgoh              #+#    #+#             */
/*   Updated: 2024/06/26 20:12:44 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_specifier(const char *format, int start, int end)
{
	int		len;

	ft_putchar_fd('%', 1);
	len = end - start + 1;
	while (start <= end)
		ft_putchar_fd(format[start++], 1);
	return (len + 1);
}
