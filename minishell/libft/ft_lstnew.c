/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:49:55 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/27 18:30:30 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with the value of
the parameter ’content’. The variable ’next’ is initialized to NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*member;

	member = malloc(sizeof(struct s_list));
	if (!member)
		return (NULL);
	(*member).next = NULL;
	(*member).content = content;
	return (member);
}
