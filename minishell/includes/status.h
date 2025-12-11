/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:35:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:25:45 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

int		get_shell_status(void);
void	set_shell_status(int status);
void	increment_line_number(void);
int		current_line_number(void);
int		*status_slot(void);

#endif
