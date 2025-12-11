/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:03:58 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/09 12:27:43 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/in_out.h"

void	ms_perror2(const char *prefix, const char *name)
{
	write(2, "minishell: ", 11);
	if (prefix && *prefix)
	{
		write(2, prefix, strlen(prefix));
		write(2, ": ", 2);
	}
	if (name && *name)
	{
		write(2, name, strlen(name));
		write(2, ": ", 2);
	}
	perror(NULL);
}

void	ms_perror1(const char *what)
{
	write(2, "minishell: ", 11);
	if (what && *what)
	{
		write(2, what, strlen(what));
		write(2, ": ", 2);
	}
	perror(NULL);
}

int	open_readonly(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ms_perror2(NULL, path);
	return (fd);
}

int	open_write_trunc(const char *path)
{
	int	fd ;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ms_perror2(NULL, path);
	return (fd);
}

int	open_write_append(const char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ms_perror2(NULL, path);
	return (fd);
}
