/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:45:08 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/21 14:05:21 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/signals.h"

static void	print_cmd_not_found(const char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd && *cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
}

static int	wait_child_code(pid_t pid)
{
	int	status;
	int	sig;

	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			return (wait_child_code(pid));
		return (1);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			return (write(STDOUT_FILENO, "^C\n", 3), 130);
		if (sig == SIGQUIT)
			return (write(STDERR_FILENO, "Quit (core dumped)\n", 19), 131);
		return (128 + sig);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	exec_child_or_die(char **argv, char ***envp)
{
	struct stat	st;
	char		*path;

	if (argv[0] && stat(argv[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		ms_perror2(NULL, argv[0]);
		exit(126);
	}
	path = ft_get_cmd_path(*envp, argv[0]);
	if (!path)
	{
		print_cmd_not_found(argv[0]);
		exit(127);
	}
	set_signals_child_defaults();
	execve(path, argv, *envp);
	ms_perror1("execve");
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

int	execute_command(char **argv, char ***envp)
{
	pid_t	pid;
	int		code;

	if (!argv || !argv[0] || !*argv[0])
	{
		write(2, "invalid command\n", 16);
		return (127);
	}
	set_signals_parent_exec();
	pid = fork();
	if (pid < 0)
		return (ms_perror1("fork"), 1);
	if (pid == 0)
		exec_child_or_die(argv, envp);
	code = wait_child_code(pid);
	set_signals_parent_idle();
	handle_sigint_feedback();
	return (code);
}

int	execute_node(t_node *node)
{
	char	**env;
	int		status;

	env = copy_env(NULL);
	status = check_node_type(node, env);
	return (status);
}
