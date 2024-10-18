/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:19:24 by cgoh              #+#    #+#             */
/*   Updated: 2024/10/07 19:44:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lst	*gnl_newlst(void)
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->str[0] = '\0';
	lst->next = NULL;
	return (lst);
}

void	gnl_lstclear(t_lst **begin)
{
	t_lst	*current;
	t_lst	*next;

	current = *begin;
	if (!current)
		return ;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*begin = NULL;
}

void	reset_buf(t_buffer *buf)
{
	buf->buffer_lst = NULL;
	buf->bytes_read = 0;
	buf->start = NULL;
	buf->end = NULL;
	buf->current_lst = NULL;
	buf->lst = NULL;
	buf->lst_last = NULL;
}
