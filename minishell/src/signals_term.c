/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:35:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:43:17 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

#ifdef ECHOCTL

static void	apply_echoctl(int on, struct termios *t)
{
	if (!t)
		return ;
	if (on)
		t->c_lflag |= ECHOCTL;
	else
		t->c_lflag &= ~ECHOCTL;
}

#else

static void	apply_echoctl(int on, struct termios *t)
{
	(void)on;
	(void)t;
}

#endif

int	term_parent_init(struct termios *orig)
{
	struct termios	t;

	if (!orig)
		return (-1);
	if (tcgetattr(STDIN_FILENO, orig) == -1)
		return (-1);
	t = *orig;
	apply_echoctl(0, &t);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
		return (-1);
	return (0);
}

int	term_parent_restore(const struct termios *orig)
{
	if (!orig)
		return (-1);
	return (tcsetattr(STDIN_FILENO, TCSANOW, orig));
}

void	term_set_echoctl(int on)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	apply_echoctl(on, &t);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
