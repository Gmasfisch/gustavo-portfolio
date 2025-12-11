/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:12 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/28 14:26:13 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Iterates the list ’lst’ and applies the function ’f’ on the content of each node.
Creates a new list resulting of the successive applications of the function ’f’.
The ’del’ function is used to delete the content of a node if needed.

- lst: address of a pointer to a node.
- f: address of the function used to iterate on the list.
- del: address of the function used to delete the content of a node if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr_init;
	t_list	*new_node;
	void	*tmp;

	ptr_init = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			tmp = f(lst->content);
			if (!tmp)
				return (ft_lstclear(&ptr_init, del), NULL);
			new_node = ft_lstnew(tmp);
			if (!new_node)
			{
				del(tmp);
				return (ft_lstclear(&ptr_init, del), NULL);
			}
			ft_lstadd_back(&ptr_init, new_node);
			lst = lst->next;
		}
	}
	return (ptr_init);
}
