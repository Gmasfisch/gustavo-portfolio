/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 01:26:41 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 21:36:26 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <termios.h>

extern volatile sig_atomic_t	g_signal;
int		*signal_mode_slot(void);

/* Termios */
int		term_parent_init(struct termios *orig);
int		term_parent_restore(const struct termios *orig);
void	term_set_echoctl(int on);
void	term_restore_line_mode(void);

/* Readline */
void	setup_readline_signals(void);

/* Signal modes */
void	set_signals_parent_idle(void);
void	set_signals_parent_heredoc(void);
void	set_signals_parent_exec(void);
void	set_signals_child_defaults(void);
void	handle_sigint_feedback(void);

#endif
