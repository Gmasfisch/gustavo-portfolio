/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:50:01 by gfischba          #+#    #+#             */
/*   Updated: 2025/05/09 18:36:38 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	char			*buffer;
	struct s_node	*next;
}t_node;

char	*get_next_line(int fd);
char	*fetch_line(t_node *list);
void	append(t_node **list, char *buf, int fd);
void	create_list(t_node **list, int fd);
int		newline(t_node *list);
int		len_until_newline(t_node *list);
void	ft_strcpy(t_node *list, char *buf);
t_node	*find_lastnode(t_node *list);
void	remaining_data(t_node **list);
void	dealloc(t_node **list, t_node *remainder_buf, char *buf);

#endif