/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:54:01 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/15 19:20:31 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC,
	NODE_GROUP,
	NODE_WILDCARD
}	t_node_type;

typedef struct s_wctx
{
	int		n;
	int		waited;
	int		last_status;
	pid_t	last_pid;
	int		saw_sigint;
}	t_wctx;

typedef struct s_node
{
	t_node_type		type;
	struct s_node	*left;
	struct s_node	*right;
	char			**cmd_args;
	char			*filename;
	char			**env;
	int				heredoc_fd;
	int				heredoc_collected;
	int				line_no;
}	t_node;

typedef struct s_pipectx
{
	int		n;
	t_node	*stages[256];
	int		**pipes;
	pid_t	*pids;
	char	***envp;
}	t_pipectx;

#endif
