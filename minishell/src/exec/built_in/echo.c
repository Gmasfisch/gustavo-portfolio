/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:13:09 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:07 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

static int	valid_n_flag(char *arg);

int	builtin_echo(char **cmd_args)
{
	int	n_flag;
	int	arg_index;

	arg_index = 1;
	n_flag = 0;
	while (cmd_args[arg_index] && valid_n_flag(cmd_args[arg_index]))
	{
		n_flag = 1;
		arg_index++;
	}
	while (cmd_args[arg_index])
	{
		write(STDOUT_FILENO, cmd_args[arg_index],
			ft_strlen(cmd_args[arg_index]));
		if (cmd_args[arg_index + 1])
			write(STDOUT_FILENO, " ", 1);
		arg_index++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

static int	valid_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
