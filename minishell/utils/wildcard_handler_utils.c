/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:36:05 by gfischba          #+#    #+#             */
/*   Updated: 2025/09/26 18:06:29 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path_and_pattern(char *token, char **pattern, char **dir)
{
	char	*path_found;

	path_found = ft_strrchr(token, '/');
	if (path_found)
	{
		if (split_path_from_pattern(token, pattern, dir, path_found) == -1)
			return (-1);
		return (1);
	}
	else
	{
		*dir = ft_strdup(".");
		*pattern = ft_strdup(token);
		if (!*dir || !*pattern)
		{
			free(*dir);
			free(*pattern);
			return (-1);
		}
	}
	return (0);
}

int	check_added(char **new_array, char *token, int *index, int added)
{
	if (added != 0)
		return (1);
	new_array[*index] = ft_strdup(token);
	if (!new_array)
		return (-1);
	(*index)++;
	return (0);
}

int	append_directory(char **new_array, int *index, char *dir, int added)
{
	int		start;
	char	*new_string;
	char	*temp;
	int		dir_len;

	start = *index - added;
	dir_len = ft_strlen(dir);
	while (start < *index)
	{
		if (dir[dir_len] != '/')
			temp = ft_strjoin(dir, "/");
		else
			temp = ft_strdup(dir);
		if (!temp)
			return (-1);
		new_string = ft_strjoin(temp, new_array[start]);
		free(temp);
		if (!new_string)
			return (-1);
		free(new_array[start]);
		new_array[start] = new_string;
		start++;
	}
	return (0);
}
