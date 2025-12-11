/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:00:34 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/27 18:11:36 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Iterates the list ’lst’ and applies the function ’f’ on the content of each node.
- lst: The address of a pointer to a node.
- f: The address of the function used to iterate on the list.
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	if (!lst || !f)
		return ;
	while (lst)
	{
		tmp = lst->next;
		f(lst->content);
		lst = tmp;
	}
}
