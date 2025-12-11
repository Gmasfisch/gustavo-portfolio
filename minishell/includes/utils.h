/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:56:42 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/15 16:57:55 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//process_line.c
void	process_line(char *line);

//parser_utils.c
int		skip_parenthesis(char **tokens, int i, int end);
int		count_tokens(char **args);
int		find_lowest_precedence(char **tokens, int start, int end);
char	**copy_tokens(char **tokens, int start, int end);
int		get_token_precedence(t_node_type type);

//utils.c
char	*get_user_input(void);
char	**dup_env(char **envp);
size_t	env_count(char **env);
char	*env_entry_dup(const char *key, const char *value, size_t *key_len);
int		env_set(const char *key, const char *value);

//tokenizer_utils.c
int		search_double_operator(char *line, int *line_index);
int		search_single_operator(char *line, int *line_index);
char	*copy_operator(char *line, int len, int *line_index);
char	*copy_word(char *line, int *line_index);

//expansion_utils.c
int		handle_var_expansion(char *token, int *i, char *buf, int buf_index);
int		copy_unquoted(char *token, int *i, char *buf, int buf_index);
char	*ft_get_env(const char *name);

//wildcard_handler_utils.c
int		find_path_and_pattern(char *token, char **pattern, char **dir);
int		check_added(char **new_array, char *token, int *index, int added);
int		append_directory(char **new_array, int *index, char *dir, int added);

//main
void	free_split(char **paths);
char	**copy_env(char **envp);

#endif
