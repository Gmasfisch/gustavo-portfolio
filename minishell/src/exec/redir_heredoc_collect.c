/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_collect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:45:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 16:59:22 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	heredoc_reader_process(int pipefd[2], char *delimiter);

static int	precollect_single_heredoc(t_node *node)
{
	int	pipefd[2];
	int	status;

	if (!node || node->heredoc_collected)
		return (0);
	status = heredoc_reader_process(pipefd, node->filename);
	if (status != 0)
		return (status);
	node->heredoc_fd = pipefd[0];
	node->heredoc_collected = 1;
	return (0);
}

int	precollect_heredocs(t_node *node)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_HEREDOC)
	{
		status = precollect_single_heredoc(node);
		if (status != 0)
			return (status);
	}
	status = precollect_heredocs(node->left);
	if (status != 0)
		return (status);
	return (precollect_heredocs(node->right));
}

void	cleanup_heredoc_fds(t_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_HEREDOC && node->heredoc_collected
		&& node->heredoc_fd >= 0)
	{
		close(node->heredoc_fd);
		node->heredoc_fd = -1;
		node->heredoc_collected = 0;
	}
	cleanup_heredoc_fds(node->left);
	cleanup_heredoc_fds(node->right);
}
