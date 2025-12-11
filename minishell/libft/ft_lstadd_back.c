/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:49:31 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/27 16:28:28 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Adds the node ’new’ at the end of the list.
- lst: The address of a pointer to the first link of a list.
- new: The address of a pointer to the node to be added to the list.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
