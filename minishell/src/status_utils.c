/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:36:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:54:25 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/status.h"

int	*status_slot(void)
{
	static int	status = 0;

	return (&status);
}
