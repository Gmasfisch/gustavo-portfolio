/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:36:01 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/14 15:20:55 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# include "../libft/libft.h"
# include "built_in.h"
# include "parser.h"
# include "utils.h"
# include "structs.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <dirent.h>
# include "exec.h"
# include "clean.h"
# include "signals.h"
# include "status.h"

#endif
