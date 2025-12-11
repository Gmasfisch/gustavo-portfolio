/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:45:22 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/21 15:52:49 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Outputs the string ’s’ to the given file descriptor
followed by a newline.
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
