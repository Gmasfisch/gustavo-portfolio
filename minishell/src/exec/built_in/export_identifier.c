/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:55:00 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:09 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

int	export_is_valid_identifier(const char *arg)
{
	size_t	i;

	if (!arg || !*arg)
		return (0);
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_identifier_error(const char *arg)
{
	if (!arg)
		return ;
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	set_shell_status(1);
}
