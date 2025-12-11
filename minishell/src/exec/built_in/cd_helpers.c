/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:17:28 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:05 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*dup_oldpwd(void)
{
	const char	*pwd_env;
	char		*dup;

	pwd_env = ft_get_env("PWD");
	if (pwd_env != NULL)
		dup = ft_strdup(pwd_env);
	else
		dup = getcwd(NULL, 0);
	if (dup == NULL)
		dup = ft_strdup("");
	return (dup);
}

char	*get_newpwd(const char *target)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		cwd = ft_strdup(target);
	return (cwd);
}

void	print_if_dash(char **args, const char *newpwd)
{
	if (args[1] != NULL)
	{
		if (ft_strcmp(args[1], "-") == 0)
		{
			write(1, newpwd, ft_strlen(newpwd));
			write(1, "\n", 1);
		}
	}
}
