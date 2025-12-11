/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_term_restore.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:28:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 01:28:00 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

void	term_restore_line_mode(void)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	t.c_lflag |= ICANON;
	t.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
