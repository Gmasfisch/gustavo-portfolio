/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:25:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:18:27 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define SIG_MODE_IDLE 0
#define SIG_MODE_EXEC 1
#define SIG_MODE_HEREDOC 2

static void	sigint_parent_handler(int sig)
{
	int	mode;

	g_signal = sig;
	mode = *signal_mode_slot();
	if (mode != SIG_MODE_EXEC)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		if (mode == SIG_MODE_IDLE)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			return ;
		}
	}
}

static void	configure_parent_signals(int mode)
{
	struct sigaction	sa;

	*signal_mode_slot() = mode;
	if (mode == SIG_MODE_EXEC)
		signal(SIGINT, SIG_IGN);
	else
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = sigint_parent_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_parent_idle(void)
{
	term_restore_line_mode();
	term_set_echoctl(0);
	configure_parent_signals(SIG_MODE_IDLE);
}

void	set_signals_parent_heredoc(void)
{
	term_restore_line_mode();
	term_set_echoctl(0);
	configure_parent_signals(SIG_MODE_HEREDOC);
}

void	set_signals_parent_exec(void)
{
	term_set_echoctl(0);
	configure_parent_signals(SIG_MODE_EXEC);
}
