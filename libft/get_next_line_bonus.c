/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:49:40 by gfischba          #+#    #+#             */
/*   Updated: 2025/02/27 16:34:48 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_node	*list[4096];
	char			*next_line;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(list, fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = fetch_line(list[fd]);
	remaining_data(&list[fd]);
	return (next_line);
}

char	*fetch_line(t_node *list)
{
	int		strlen;
	char	*next_line;

	if (list == NULL)
		return (NULL);
	strlen = len_until_newline(list);
	next_line = malloc(strlen + 1);
	if (!next_line)
		return (NULL);
	ft_strcpy(list, next_line);
	return (next_line);
}

void	append(t_node **list, char *buf, int fd)
{
	t_node	*new_node;
	t_node	*last_node;

	last_node = find_lastnode(list[fd]);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	if (last_node == NULL)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->buffer = buf;
	new_node->next = NULL;
}

void	create_list(t_node **list, int fd)
{
	int		chars_read;
	char	*buf;

	while (!newline(list[fd]))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (!chars_read)
		{
			free(buf);
			return ;
		}
		buf[chars_read] = '\0';
		append(list, buf, fd);
	}
}

int	newline(t_node *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->buffer[i] && i < BUFFER_SIZE)
		{
			if (list->buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}
