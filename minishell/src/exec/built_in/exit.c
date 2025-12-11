/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:12:26 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/21 19:35:03 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

#include <limits.h>

static int	status_is_num(const char *args)
{
	int	i;

	i = 0;
	if (args[i] == '-' || args[i] == '+')
		i++;
	if (!ft_strcmp(args, "9223372036854775807"))
		return (1);
	if (!args[i])
		return (0);
	while (args[i])
	{
		if (!ft_isdigit(args[i]) || atoll(args) >= LLONG_MAX)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args, ft_strlen(args));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	too_many_args(void)
{
	write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, "too many arguments\n", 19);
}

int	builtin_exit(char **args)
{
	int	status;
	int	i;

	status = 0;
	i = count_tokens(args);
	if (args[1] && !status_is_num(args[1]))
	{
		write(STDERR_FILENO, "exit\n", 5);
		exit (2);
	}
	if (i > 2)
	{
		too_many_args();
		return (1);
	}
	if (args[1])
		status = ft_atoi(args[1]);
	write(1, "exit\n", 5);
	exit(status % 256);
}
