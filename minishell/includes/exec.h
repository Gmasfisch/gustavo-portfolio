/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:57:02 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:46:27 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
//for t_pid
# include <sys/types.h>

# include <stdio.h>
# include <fcntl.h>
# include "built_in.h"
# include "in_out.h"
# include "signals.h"
# include "structs.h"

int		exec_and(t_node *left, t_node *right);
int		exec_or(t_node *left, t_node *right);
int		execute_node(t_node *node);
int		execute_command(char **argv, char ***envp);
int		execute_pipe(t_node *left, t_node *right);
void	ms_update_underscore_from_args(char **argv);
void	ms_update_underscore_from_node(t_node *node);

char	*ft_get_cmd_path(char **envp, char *cmd);

void	restore_stdout(int saved);

int		is_builtin_cmd_node(t_node *n);

// exec utils
int		run_subshell(t_node *child);
int		exec_node_command(t_node *node, char ***envp);
int		exec_node_redir(t_node *n);
int		check_node_type(t_node *node, char **env);

// pipes utils
void	free_pipes(int **pipes, int n_pipes);
void	close_all_pipes(int **pipes, int n_pipes);
void	child_wire_fds(int i, int n, int **pipes);
int		**alloc_pipes(int n_pipes);
int		build_stages(t_node *root, t_node **stages, int max, int *out_n);
int		wait_all_and_get_last(pid_t *pids, int n);
int		exec_pipeline_root(t_node *root);
void	wctx_init(t_wctx *w, pid_t *pids, int n);
void	parent_close_pipes(t_pipectx *c);
int		init_ctx(t_pipectx *c, t_node *root);

int		execute_heredoc(t_node *heredoc, t_node *cmd);
int		precollect_heredocs(t_node *node);
void	cleanup_heredoc_fds(t_node *node);

#endif
