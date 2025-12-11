/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:25:34 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/27 15:16:51 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Adds the node ’new’ at the beginning of the list.
- lst: The address of a pointer to the first link of a list.
- new: The address of a pointer to the node to be added to the list.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	(*new).next = *lst;
	*lst = new;
}
