/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:05:14 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:27:47 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "../../libft.h"

typedef struct s_format
{
	char	*flags;
	int		width;
	int		precision;
	int		fd;
}	t_format;
int		ft_dprintf(int fd, const char *format, ...);
int		parse_str(va_list va_ptr, int *i, const char *format,
			t_format *format_lst);
int		print_char(t_format *format_lst, char c);
int		print_d(t_format *format_lst, int n);
int		print_p(t_format *format_lst, void *p);
int		print_pct(t_format *format_lst);
int		print_s(t_format *format_lst, char *str);
int		print_specifier(const char *format, int start, int end,
			t_format *format_lst);
int		print_u(t_format *format_lst, unsigned int n);
int		print_x(t_format *format_lst, unsigned int n, char format);

#endif
