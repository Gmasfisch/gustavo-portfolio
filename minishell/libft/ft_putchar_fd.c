/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:59 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/21 15:40:30 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Outputs the character ’c’ to the given file
descriptor.
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
