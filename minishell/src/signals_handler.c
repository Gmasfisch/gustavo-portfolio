/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 01:30:46 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 20:06:55 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define SIG_MODE_IDLE 0

int	*signal_mode_slot(void)
{
	static int	mode = SIG_MODE_IDLE;

	return (&mode);
}

void	set_signals_child_defaults(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
