/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segments_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:43:00 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 16:01:09 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Function: expand_variable
**	---------------------------------
**	This function expand the variables if it possible to expand.

**	Parameters:
**		input:		input string.
**		curr_pos:	current position on string.

**	Return:
**		Non.
*/
static int	expand_variable(char *old_str, char **new_str, int *curr_pos)
{
	int	start;

	if (old_str[*curr_pos + 1] == '?')
		return (2);
	if (old_str[*curr_pos + 1] == ' ')
		return (1);
	(*curr_pos)++;
	start = *curr_pos;
	while (old_str[*curr_pos] && old_str[*curr_pos] != ' '
		&& !is_quote(old_str[*curr_pos]))
		(*curr_pos)++;
	if (start != *curr_pos)
		add_c_to_string(new_str, '\\');
	else
		return (0);
	return (1);
}

/*
**	Function: skip_quote
**	---------------------------------
**	This function skip all the quoted content and
**	give an error when quotes arent closed

**	Parameters:
**		input:		input string.
**		quote:		char ' or " that was is that position.
**		curr_pos:	current position on string.

**	Return:
**		Non.
*/
static int	skip_quote(char *str, char **new_str, char quote, int *curr_pos)
{
	while (str[++(*curr_pos)])
	{
		if (quote == '\"' && str[*curr_pos] == '$')
			expand_variable(str, new_str, curr_pos);
		if (str[*curr_pos] == quote)
		{
			(*curr_pos)++;
			break ;
		}
		add_c_to_string(new_str, str[*curr_pos]);
	}
	return (1);
}

void	parse_segment_conditions(char *str, char **new_str, int *curr_pos)
{
	if (is_quote(str[*curr_pos]))
	{
		if (!skip_quote(str, new_str, str[*curr_pos], curr_pos))
			exit_program("bateu nas quotes", 0);
	}
	else if (str[*curr_pos] == '$')
	{
		if (!expand_variable(str, new_str, curr_pos))
			exit_program("bateu na expand variable", 0);
	}
	else
		add_c_to_string(new_str, str[(*curr_pos)++]);
}
