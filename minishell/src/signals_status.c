/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 01:30:46 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 21:36:57 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

volatile sig_atomic_t	g_signal = 0;

void	setup_readline_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}
