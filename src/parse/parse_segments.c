/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:43:00 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 15:11:12 by rgomes-c         ###   ########.fr       */
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

static void	parse_segment_cmd(char **str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		if (is_quote((*str)[i]))
		{
			if (!skip_quote(*str, &new_str, (*str)[i], &i))
				exit_program("bateu nas quotes", 0);
		}
		else if ((*str)[i] == '$')
		{
			if (!expand_variable(*str, &new_str, &i))
				exit_program("bateu na expand variable", 0);
		}
		else
		{
			add_c_to_string(&new_str, (*str)[i]);
			i++;
		}
	}
	free(*str);
	*str = new_str;
}

static void	parse_segment_red(char **str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	if (!(*str))
		return ;
	if ((*str)[i] == (*str)[i + 1])
		add_c_to_string(&new_str, (*str)[i++]);
	add_c_to_string(&new_str, (*str)[i++]);
	while (is_space((*str)[i]))
		i++;
	if (is_greatorless((*str)[i]))
		exit_program("novamente sintax error", 0);
	while ((*str)[i])
	{
		if (is_quote((*str)[i]))
		{
			if (!skip_quote(*str, &new_str, (*str)[i], &i))
				exit_program("bateu nas quotes", 0);
		}
		else if ((*str)[i] == '$')
		{
			if (!expand_variable(*str, &new_str, &i))
				exit_program("bateu na expand variable", 0);
		}
		else
			add_c_to_string(&new_str, (*str)[i++]);
	}
	free(*str);
	*str = new_str;
}

void	parse_segments(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		i = -1;
		while (seg->cmd && seg->cmd[++i])
			parse_segment_cmd(&seg->cmd[i]);
		i = -1;
		while (seg->red && seg->red[++i])
			parse_segment_red(&seg->red[i]);
		temp = temp->next;
	}
}
