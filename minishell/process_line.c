/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 01:23:52 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/15 21:22:53 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	shell_status_helper(int collect_status, t_node *ast)
{
	if (collect_status == -2)
		set_shell_status(130);
	else
		set_shell_status(1);
	cleanup_heredoc_fds(ast);
	free_ast(ast);
}

void	process_line(char *line)
{
	char	**args;
	t_node	*ast;
	int		token_count;
	int		collect_status;

	args = tokenizer(line);
	if (!args)
		return ;
	token_count = count_tokens(args);
	ast = parser(args, 0, token_count - 1);
	if (ast)
	{
		collect_status = precollect_heredocs(ast);
		if (collect_status != 0)
			shell_status_helper(collect_status, ast);
		else
		{
			execute_node(ast);
			cleanup_heredoc_fds(ast);
			free_ast(ast);
		}
	}
	free_split(args);
}
