/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:14:23 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/15 19:17:59 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint_feedback(void)
{
	if (g_signal == SIGINT)
	{
		set_shell_status(130);
		g_signal = 0;
	}
}
