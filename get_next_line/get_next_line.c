/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:04:03 by gmasfisch         #+#    #+#             */
/*   Updated: 2025/03/06 16:17:17 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_node	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	allocate_list(&list, fd);
	if (!list)
		return (NULL);
	line = fetch_line(&list);
	if (!line)
	{
		free_list(&list);
		return (NULL);
	}
	return (line);
}

void	allocate_list(t_node **list, int fd)
{
	t_node	*new_node;
	int		bytes_read;

	while (!find_newline(*list))
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			return ;
		new_node->buf = malloc(BUFFER_SIZE + 1);
		if (!new_node->buf)
		{
			free(new_node);
			return ;
		}
		bytes_read = read(fd, new_node->buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(new_node->buf);
			free(new_node);
			return ;
		}
		new_node->buf[bytes_read] = '\0';
		new_node->next = NULL;
		add_nodes(list, new_node);
	}
}

char	*fetch_line(t_node **list)
{
	int		len;
	t_node	*temp;
	char	*line;

	temp = *list;
	len = len_newline(temp);
	if (len == 0) 
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	return (copy_data(list, line, len), line);
}

void	copy_data(t_node **list, char *line, int len)
{
	int		i;
	int		j;
	t_node	*temp;
	t_node	*prev;

	temp = *list;
	prev = NULL;
	i = 0;
	while (temp && i < len)
	{
		j = 0;
		while (temp->buf[j] && i < len)
			line[i++] = temp->buf[j++];
		if (temp->buf[j])
		{
			shift_buffer(temp->buf, j);
			break ;
		}
		prev = temp;
		temp = temp->next;
		free(prev->buf);
		free(prev);
		*list = temp;
	}
	line[len] = '\0';
}

void	shift_buffer(char *buf, int shift)
{
	int	i;

	i = 0;
	while (buf[shift])
		buf[i++] = buf[shift++];
	buf[i] = '\0';
}

/*int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char    *line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
}*/