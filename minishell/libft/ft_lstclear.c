/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:12:15 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/27 18:00:01 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Deletes and frees the given node and every successor of that node,
using the function ’del’ and free(3).
Finally, the pointer to the list must be set to NULL.

- lst: The address of a pointer to a node.
- del: The address of the function used to delete the content of the node.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
