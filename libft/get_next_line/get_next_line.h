/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:43:35 by cgoh              #+#    #+#             */
/*   Updated: 2024/11/29 02:34:16 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1000
# endif
# define MAX_FD	1024
# include <stdlib.h>
# include <unistd.h>

typedef struct s_lst
{
	char			str[BUFFER_SIZE + 1];
	struct s_lst	*next;
}	t_lst;
typedef struct s_buffer
{
	t_lst			*buffer_lst;
	ssize_t			bytes_read;
	char			*start;
	char			*end;
	t_lst			*current_lst;
	t_lst			*lst;
	t_lst			*lst_last;
}	t_buffer;
typedef struct s_vars
{
	char			*line;
	unsigned int	line_size;
}	t_vars;
char	*get_next_line(int fd);
t_lst	*gnl_newlst(void);
void	gnl_lstclear(t_lst **begin);
void	reset_buf(t_buffer *buf);

#endif
