/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:34:42 by gfischba          #+#    #+#             */
/*   Updated: 2025/03/06 17:10:51 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	char			*buf;
	struct s_node	*next;
}t_node;

char	*get_next_line(int fd);
void	allocate_list(t_node **list, int fd);
char	*fetch_line(t_node **list);
void	copy_data(t_node **list, char *line, int len);
int		find_newline(t_node *list);
void	free_list(t_node **list);
void	add_nodes(t_node **list, t_node *new_node, int fd);
t_node	*find_lastnode(t_node *list);
void	shift_buffer(char *buf, int shift);
int		len_newline(t_node *temp);

#endif