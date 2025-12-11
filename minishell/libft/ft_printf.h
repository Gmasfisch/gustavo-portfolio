/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:49:47 by mlemoula          #+#    #+#             */
/*   Updated: 2025/04/19 16:32:16 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft.h"
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_print_pc(char *s, char arg, int *print_count);
void	ft_print_s(char *arg, int *print_count);
void	ft_print_x_upx(unsigned int arg, int *print_count, char c);
void	ft_print_id(int arg, int *print_count);
void	ft_print_u(unsigned int arg, int *print_count);
void	ft_print_p(void *ptr, int *print_count);

#endif