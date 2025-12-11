/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:58:41 by mlemoula          #+#    #+#             */
/*   Updated: 2025/10/14 15:20:53 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "utils.h"

void	free_ast(t_node *node);
void	free_split(char **paths);

#endif