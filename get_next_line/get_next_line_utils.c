/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:02:47 by gfischba          #+#    #+#             */
/*   Updated: 2025/03/06 16:17:38 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(t_node *list)
{
	int		i;
	t_node	*temp;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->buf[i])
		{
			if (temp->buf[i] == '\n')
				return (1);
			i++;
		}
		temp = temp->next;
	}
	return (0);
}

void	free_list(t_node **list)
{
	t_node	*tmp;

	if (!list || !(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = tmp;
	}
}

void	add_nodes(t_node **list, t_node *new_node)
{
	t_node	*last_node;

	last_node = find_lastnode(*list);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
}

t_node	*find_lastnode(t_node *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	len_newline(t_node *temp)
{
	int	i;
	int	len;

	len = 0;
	while (temp)
	{
		i = 0;
		while (temp->buf[i] && temp->buf[i] != '\n')
			i++;
		len += i;
		if (temp->buf[i] == '\n')
		{
			len++;
			break ;
		}
		temp = temp->next;
	}
	return (len);
}
