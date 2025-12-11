/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:41:51 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/03 17:43:05 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_wildcard(char **new_array, char *token, int *index)
{
	DIR		*directory;
	char	*dir;
	char	*pattern;
	int		added;
	int		path_found;

	path_found = find_path_and_pattern(token, &pattern, &dir);
	directory = open_directory(new_array, token, dir, index);
	if (directory == NULL)
	{
		free(pattern);
		return (-1);
	}
	added = check_directory(directory, pattern, new_array, index);
	if (check_added(new_array, token, index, added) == -1)
		return (-1);
	if (path_found == 1)
		append_directory(new_array, index, dir, added);
	closedir(directory);
	free(pattern);
	free(dir);
	if (added == -1)
		return (-1);
	return (0);
}

int	split_path_from_pattern(char *token, char **pattern,
				char **dir, char *path)
{
	int	path_len;

	path_len = path - token;
	*dir = malloc(path_len + 1);
	if (!*dir)
		return (-1);
	ft_strncpy(*dir, token, path_len);
	(*dir)[path_len] = '\0';
	*pattern = ft_strdup(path + 1);
	if (!*pattern)
	{
		free (*dir);
		return (-1);
	}
	return (0);
}

int	match(char *pattern, char *name)
{
	if (*pattern == '\0' && *name == '\0')
		return (1);
	if (*pattern == '*')
		return (match(pattern + 1, name)
			|| (*name && match(pattern, name + 1)));
	if (*pattern == *name)
		return (match(pattern + 1, name + 1));
	return (0);
}

DIR	*open_directory(char **new_array, char *token,
	char *dir, int *index)
{
	DIR	*directory;

	directory = opendir(dir);
	if (!directory)
	{
		free(new_array[*index]);
		new_array[*index] = ft_strdup(token);
		if (!new_array[*index])
			return (NULL);
		(*index)++;
		return (NULL);
	}
	return (directory);
}

int	check_directory(DIR *directory, char *pattern, char **new_array, int *index)
{
	struct dirent	*entry;
	int				added;
	int				token_pos;

	added = 0;
	entry = readdir(directory);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(directory);
			continue ;
		}
		if (match(pattern, entry->d_name))
		{
			token_pos = *index;
			new_array[token_pos] = ft_strdup(entry->d_name);
			if (!new_array[token_pos])
				return (-1);
			(*index)++;
			added++;
		}
		entry = readdir(directory);
	}
	return (added);
}
