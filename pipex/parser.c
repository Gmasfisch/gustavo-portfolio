/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:22:58 by gfischba          #+#    #+#             */
/*   Updated: 2025/06/16 08:24:58 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*extract_arg(const char *s, int *i);
static int	skip_spaces(const char *s, int i);
static int	handle_quote(const char *s, int *i, char quote);
static int	count_arguments(const char *s);

char	**parser(const char *cmd)
{
	int		i;
	int		arg;
	int		argc;
	char	**args;

	i = 0;
	arg = 0;
	argc = 0;
	argc = count_arguments(cmd);
	args = malloc(sizeof(char *) * (argc + 1));
	if (!args)
		return (NULL);
	while (cmd[i])
	{
		i = skip_spaces(cmd, i);
		if (!cmd[i])
			break ;
		args[arg++] = extract_arg(cmd, &i);
	}
	args[arg] = NULL;
	return (args);
}

static char	*extract_arg(const char *s, int *i)
{
	char	buf[1024];
	int		buf_i;
	int		in_single;
	int		in_double;

	buf_i = 0;
	in_single = 0;
	in_double = 0;
	while (s[*i] && (in_single || in_double || s[*i] != ' '))
	{
		if (s[*i] == '\'' && !in_double)
			in_single = !in_single;
		else if (s[*i] == '"' && !in_single)
			in_double = !in_double;
		else
			buf[buf_i++] = s[*i];
		(*i)++;
	}
	buf[buf_i] = '\0';
	return (ft_strdup(buf));
}

static int	skip_spaces(const char *s, int i)
{
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

static int	handle_quote(const char *s, int *i, char quote)
{
	if (s[*i] != quote)
		return (0);
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
	return (1);
}

static int	count_arguments(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == '\'' || s[i] == '"')
				handle_quote(s, &i, s[i]);
			else
				i++;
		}
	}
	return (count);
}
