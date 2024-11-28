/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:44:32 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:34:58 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_find_end(t_buffer *buf, t_vars *vars)
{
	while (buf->end[0] && buf->end[0] != '\n')
	{
		vars->line_size++;
		buf->end++;
	}
	if (buf->end[0] == '\n')
		vars->line_size++;
}

static void	fill_line(t_buffer *buf, t_vars *vars)
{
	int		i;

	vars->line = malloc((vars->line_size + 1) * sizeof(char));
	if (!vars->line)
		return ;
	if (!buf->current_lst)
		buf->current_lst = buf->lst;
	i = 0;
	while (buf->start[0] && buf->start[0] != '\n')
	{
		vars->line[i++] = buf->start[0];
		buf->start++;
		if (!buf->start[0] && buf->start != buf->end)
		{
			buf->current_lst = buf->current_lst->next;
			buf->start = buf->current_lst->str;
		}
	}
	if (buf->end[0] == '\n')
		vars->line[i++] = '\n';
	vars->line[i] = '\0';
	if (buf->start[0])
		buf->start++;
	else
		buf->start = NULL;
}

static int	append_lst(t_buffer *buf)
{
	buf->buffer_lst = gnl_newlst();
	if (!buf->buffer_lst)
		return (0);
	if (!buf->lst)
	{
		buf->lst = buf->buffer_lst;
		buf->lst_last = buf->buffer_lst;
	}
	else
	{
		buf->lst_last->next = buf->buffer_lst;
		buf->lst_last = buf->buffer_lst;
	}
	return (1);
}

static int	do_buffer_reading(int fd, t_buffer *buf, t_vars *vars)
{
	if (!append_lst(buf))
		return (0);
	if (!buf->start || !buf->start[0])
	{
		buf->start = buf->buffer_lst->str;
		buf->current_lst = buf->buffer_lst;
	}
	if (!buf->end)
		buf->end = buf->start;
	buf->bytes_read = read(fd, buf->buffer_lst->str, BUFFER_SIZE);
	if (buf->bytes_read < 0)
		return (0);
	while (buf->bytes_read > 0)
	{
		buf->buffer_lst->str[buf->bytes_read] = '\0';
		buf->end = buf->buffer_lst->str;
		gnl_find_end(buf, vars);
		if (buf->end[0] == '\n')
			return (1);
		if (!append_lst(buf))
			return (0);
		buf->end = buf->buffer_lst->str;
		buf->bytes_read = read(fd, buf->buffer_lst->str, BUFFER_SIZE);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	t_vars			vars;

	if (fd < 0 || fd >= MAX_FD)
		return (gnl_lstclear(&buf.lst), reset_buf(&buf), NULL);
	vars.line_size = 0;
	if (buf.start)
	{
		buf.end = buf.start;
		gnl_find_end(&buf, &vars);
	}
	if (!buf.start || (buf.end && !buf.end[0]))
		if (!do_buffer_reading(fd, &buf, &vars))
			return (gnl_lstclear(&buf.lst), reset_buf(&buf), NULL);
	if (!vars.line_size)
		return (gnl_lstclear(&buf.lst), reset_buf(&buf), NULL);
	fill_line(&buf, &vars);
	if (!vars.line)
	{
		gnl_lstclear(&buf.lst);
		reset_buf(&buf);
	}
	return (vars.line);
}
