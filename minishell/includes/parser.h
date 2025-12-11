/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:08:12 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/14 20:53:44 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include <dirent.h>

//parser.c
t_node		*parser(char **tokens, int start, int end);
t_node_type	get_token_type(char *token);
t_node		*create_command_or_group(char **tokens, int start, int end);
t_node		*create_operator_node(char **tokens, int start,
				int end, int op_index);
t_node		*handle_logic_op(char **tokens, int start, int end, int op_index);
t_node		*handle_redir_op(char **tokens, int start, int end, int op_index);
t_node		*alloc_op_node(char **tokens, int op_index);

//tokenizer.c
char		**tokenizer(char *line);
char		*handle_quotes(char *line, int *line_index);
int			skip_spaces(char *line, int i);

//expansion.c
char		**expansion(char **args);
char		**expand_tokens(char **args);
char		*expand_word(const char *token);
void		handle_expansion(char *token, char **new_array, int *array_index);
int			copy_single_quotes(char *token, int *i, char *buf, int buf_index);
int			copy_double_quotes(char *token, int *i, char *buf, int buf_index);
char		*expand_var(char *token, int *i);
void		handle_expansion_heredoc(char *token, 
				char **new_array, int *array_index);
char		**expansion_heredoc(char **args);
void		store_or_expand(char **arr, int *idx, const char *buf);
char		**tokenizer_heredoc(char *line);
char		*copy_word_heredoc(char *line, int *line_index);

//wildcard_handler.c
int			handle_wildcard(char **token_array, char *token, int *index);
int			split_path_from_pattern(char *token, char **pattern,
				char **dir, char *path);
DIR			*open_directory(char **token_array,
				char *token, char *dir, int *index);
int			match(char *pattern, char *name);
int			check_directory(DIR *directory, char *pattern,
				char **token_array, int *index);

#endif
