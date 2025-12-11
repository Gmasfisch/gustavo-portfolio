/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:56:42 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/15 16:58:26 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IN_OUT_H
# define IN_OUT_H

# include "structs.h"
# include "exec.h"
# include "structs.h"   // t_node

//for t_pid
# include <sys/types.h>

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

// --- erreurs
void	ms_perror2(const char *prefix, const char *name);
void	ms_perror1(const char *what);

// --- open/dup/close sûrs
int		open_readonly(const char *path);
int		open_write_trunc(const char *path);
int		open_write_append(const char *path);

int		dup2_safe(int from, int to);
int		close_fd(int fd);

// --- wait & statut
int		wait_collect_exitcode(pid_t pid);

// --- utilitaires stdio (pour plus tard: builtins en parent)
int		save_stdio(int saved[2]);
int		restore_stdio(int saved[2]);

// redir_in.h
void	heredoc_write_loop(int write_fd, char *delimiter);
int		execute_redir_in(t_node *cmd, const char *filename);
int		execute_redir_out(t_node *cmd, const char *filename,
			int append);
int		execute_redir_in_parent(t_node *cmd, const char *filename);
int		execute_redir_out_parent(t_node *cmd, const char *filename,
			int append);

#endif
