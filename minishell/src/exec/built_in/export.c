/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 23:14:24 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 20:27:25 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/built_in.h"

static void	print_variables(void);
static char	**sort_env(char **envp);

int	builtin_export(char **args)
{
	char	**envp;
	int		error;
	int		i;

	envp = copy_env(NULL);
	error = 0;
	i = 1;
	if (!args[1])
		print_variables();
	while (args && args[i])
	{
		if (!export_is_valid_identifier(args[i]))
		{
			export_identifier_error(args[i]);
			error = 1;
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '=') && export_store(&envp, args[i]))
			error = 1;
		i++;
	}
	set_shell_status(error);
	return (error);
}

static void	print_variables(void)
{
	char	**envp;
	int		i;

	i = 0;
	envp = copy_env(NULL);
	envp = sort_env(envp);
	while (envp[i])
		printf("declare -x %s\n", envp[i++]);
}

static char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) < 0)
			{
				tmp = envp[j];
				envp[j] = envp[i];
				envp[i] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}
