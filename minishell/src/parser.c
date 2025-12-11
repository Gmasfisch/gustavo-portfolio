/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:57:13 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/14 15:07:30 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*parser(char **tokens, int start, int end)
{
	int	op_index;

	if (start > end)
		return (NULL);
	op_index = find_lowest_precedence(tokens, start, end);
	if (op_index != -1)
		return (create_operator_node(tokens, start, end, op_index));
	return (create_command_or_group(tokens, start, end));
}
