/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:44:05 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/27 16:11:03 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

void	here_doc_mode(t_pipex *pipex, char **argv, int argc);
void	read_heredoc_input(int write_fd, const char *limiter);

#endif