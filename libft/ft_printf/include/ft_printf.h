/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:05:14 by cgoh              #+#    #+#             */
/*   Updated: 2024/09/20 18:32:49 by cgoh             ###   ########.fr       */
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
}	t_format;
int		ft_printf(const char *format, ...);
int		get_length(va_list va_ptr, const char *format, t_format *format_lst);
int		print_replacement(t_format *f_lst, char specifier, va_list va_ptr);
int		parse_str(va_list va_ptr, int *i, const char *format,
			t_format *format_lst);
int		parse_flags(t_format *format_lst, int *i, const char *format);
int		parse_width(t_format *format_lst, int *i, const char *format);
int		parse_precision(t_format *format_lst, int *i, const char *format);
int		print_char(t_format *format_lst, char c);
void	print_formatted_char(char c, int width, int left);
int		print_d(t_format *format_lst, int n);
char	*malloc_str_d(int n, char *flags, int precision);
int		fill_formatted_d(char *formatted_d, t_format *format_lst, int n);
void	print_formatted_d(char *formatted_d, t_format *format_lst);
int		print_p(t_format *format_lst, void *p);
char	*malloc_str_p(void *p, char *flags, int precision);
int		fill_formatted_p(char *formatted_p, t_format *format_lst, void *p);
void	print_formatted_p(char *formatted_p, t_format *format_lst);
int		print_pct(void);
int		print_s(t_format *format_lst, char *str);
int		print_formatted_s(char *str, int width, int precision, int left);
char	*get_substr(char *str, int precision);
int		print_specifier(const char *format, int start, int end);
int		print_u(t_format *format_lst, unsigned int n);
char	*malloc_str_u(unsigned int n, int precision);
int		fill_formatted_u(char *formatted_u, unsigned int n);
void	print_formatted_u(char *formatted_u, t_format *format_lst);
int		print_x(t_format *format_lst, unsigned int n, char format);
char	*malloc_str_x(unsigned int n, t_format *format_lst, char format);
int		fill_formatted_x(char *formatted_x,
			unsigned int n, char format, t_format *format_lst);
void	print_formatted_x(char *formatted_x, t_format *format_lst);

#endif
