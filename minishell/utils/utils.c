/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:24:25 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/21 13:51:16 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_ctx(t_pipectx *c, t_node *root)
{
	c->n = 0;
	c->pipes = NULL;
	c->pids = NULL;
	if (build_stages(root, c->stages, 256, &c->n) != 0)
		return (1);
	return (0);
}

int	check_file(t_node *node, int op_index, int end)
{
	if (op_index + 1 > end)
	{
		write(2, "Syntax error: missing filename\n", 31);
		free(node);
		set_shell_status(2);
		return (1);
	}
	return (0);
}

char	*get_user_input(void)
{
	char	*line;
	char	prompt[4096];
	char	*cwd;

	prompt[0] = '\0';
	cwd = ft_get_env("PWD");
	if (!cwd)
		cwd = ft_strdup("minishell>");
	ft_strlcpy(prompt, cwd, sizeof(prompt));
	free(cwd);
	ft_strlcat(prompt, "$ ", sizeof(prompt));
	line = readline(prompt);
	if (!line)
		return (NULL);
	if (g_signal)
		handle_sigint_feedback();
	if (line && *line)
		add_history(line);
	if (ft_strlen(line) > 4096)
	{
		write(2, "line too long\n", 15);
		free(line);
		return (ft_strdup(""));
	}
	return (line);
}
