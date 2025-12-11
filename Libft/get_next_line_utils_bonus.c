/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:49:59 by gfischba          #+#    #+#             */
/*   Updated: 2025/02/18 14:09:02 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	len_until_newline(t_node *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	ft_strcpy(t_node *list, char *buf)
{
	int	i;
	int	k;

	k = 0;
	while (list)
	{
		i = 0;
		while (list->buffer[i])
		{
			if (list->buffer[i] == '\n')
			{
				buf[k++] = '\n';
				buf[k] = '\0';
				return ;
			}
			buf[k++] = list->buffer[i++];
		}
		list = list->next;
	}
	buf[k] = '\0';
}

t_node	*find_lastnode(t_node *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	remaining_data(t_node **list)
{
	t_node	*last_node;
	t_node	*remainder_buf;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	remainder_buf = malloc(sizeof(t_node));
	if (!remainder_buf || !buf)
		return ;
	last_node = find_lastnode(*list);
	i = 0;
	k = 0;
	while (last_node->buffer[i] && last_node->buffer[i] != '\n')
		i++;
	while (last_node->buffer[i] && last_node->buffer[++i])
		buf[k++] = last_node->buffer[i];
	buf[k] = '\0';
	remainder_buf->buffer = buf;
	remainder_buf->next = NULL;
	dealloc(list, remainder_buf, buf);
}

void	dealloc(t_node **list, t_node *remainder_buf, char *buf)
{
	t_node	*tmp;

	if (list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->buffer);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (remainder_buf->buffer[0])
		*list = remainder_buf;
	else
	{
		free(remainder_buf);
		free(buf);
	}
}
