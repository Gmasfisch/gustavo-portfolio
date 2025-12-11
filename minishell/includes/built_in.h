/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:15:46 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:20:52 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../libft/libft.h"
# include "minishell.h"

//from builtin
int		execute_builtin(char **args, char ***env);
int		is_builtin(char *cmd);

//from builtin_env
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_env(void);
int		builtin_echo(char **args);
int		builtin_exit(char **args);
int		builtin_cd(char **args, char ***env);
int		builtin_pwd(void);
int		export_is_valid_identifier(const char *arg);
void	export_identifier_error(const char *arg);
int		export_store(char ***env, const char *assignment);

//utils
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*get_target_dir(char **args);

//cd_helpers
void	print_if_dash(char **args, const char *newpwd);
char	*dup_oldpwd(void);
char	*get_newpwd(const char *target);

#endif
