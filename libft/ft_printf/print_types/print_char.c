/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:13:05 by cgoh              #+#    #+#             */
/*   Updated: 2025/01/03 04:01:08 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	print_formatted_char(char c, int width, int left,
	t_format *format_lst)
{
	while (!left && width-- > 1)
		ft_putchar_fd(' ', format_lst->fd);
	ft_putchar_fd(c, format_lst->fd);
	while (width-- > 1)
		ft_putchar_fd(' ', format_lst->fd);
}

int	print_char(t_format *format_lst, char c)
{
	char	*flags;
	int		width;
	int		left;

	flags = format_lst->flags;
	width = format_lst->width;
	left = 0;
	if (ft_strchr(flags, '-'))
		left = 1;
	print_formatted_char(c, width, left, format_lst);
	if (width > 0)
		return (width);
	return (1);
}
