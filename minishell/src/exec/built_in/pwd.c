/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:17:42 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:11 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

int	builtin_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}
