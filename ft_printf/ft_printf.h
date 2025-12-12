/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:29:39 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/29 11:05:06 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
void	checker(va_list args, const char *format, int *count);
void	p_string(char *str, int *count);
void	p_num(int num, int *count);
void	p_hex(unsigned int nbr, int *count, const char *format);
void	p_unsigned(unsigned int nbr, int *count);
void	p_address(void *pointer, int *count);
void	ft_putchar(char c);

#endif