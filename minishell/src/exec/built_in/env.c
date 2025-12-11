/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:13:40 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:08 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

int	builtin_env(void)
{
	int		i;
	char	**envp;

	envp = copy_env(NULL);
	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
