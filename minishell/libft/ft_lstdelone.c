/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:30:33 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/27 18:00:03 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Takes as a parameter a node and frees the memory of the node’s content using
the function ’del’ given as a parameter and free the node. The memory of
’next’ must not be freed.

- lst: The node to free.
- del: The address of the function used to delete the content
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		del(lst->content);
	free(lst);
}
