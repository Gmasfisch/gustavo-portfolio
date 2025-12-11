/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_writer_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:45:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:51:37 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <errno.h>
#include <fcntl.h>

void	restore_stdout(int saved)
{
	if (saved >= 0)
	{
		dup2(saved, STDOUT_FILENO);
		close(saved);
	}
}
