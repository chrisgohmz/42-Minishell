/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:37:03 by cgoh              #+#    #+#             */
/*   Updated: 2024/05/20 21:47:37 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_node;
	t_list	*new_node;
	void	*new_content;

	first_node = NULL;
	new_node = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&first_node, del);
			return (NULL);
		}
		if (!first_node)
			first_node = new_node;
		else
			ft_lstadd_back(&first_node, new_node);
		lst = lst->next;
	}
	return (first_node);
}
