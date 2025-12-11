/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:35:41 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/21 13:42:29 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/signals.h"
#include "includes/clean.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	struct termios	term_orig;

	(void)argc;
	(void)argv;
	set_signals_parent_idle();
	setup_readline_signals();
	term_parent_init(&term_orig);
	copy_env(dup_env(envp));
	set_shell_status(0);
	while (1)
	{
		line = get_user_input();
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		increment_line_number();
		process_line(line);
		free(line);
	}
	term_parent_restore(&term_orig);
	free_split(copy_env(NULL));
	return (0);
}
