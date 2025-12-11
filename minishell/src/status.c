/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:36:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:26:02 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/status.h"

static int	*line_slot(void)
{
	static int	line = 0;

	return (&line);
}

int	get_shell_status(void)
{
	return (*status_slot());
}

void	set_shell_status(int status)
{
	char	*value;

	*status_slot() = status;
	value = ft_itoa(status);
	if (!value)
		return ;
	env_set("?", value);
	free(value);
}

void	increment_line_number(void)
{
	int	*line;

	line = line_slot();
	*line = *line + 1;
}

int	current_line_number(void)
{
	return (*line_slot());
}
