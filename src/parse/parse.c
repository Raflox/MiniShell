/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 17:08:44 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Function: get_segment_red
**	---------------------------------
**	This function gets a redirection.
**	Then will be treated forward.

**	Parameters:
**		red_array:	pointer to the redirection array.
		seg:		the segment string.
		curr_pos:	current position of the segment string.

**	Return:
**		Non.
*/
void	get_segment_red(char ***red_array, char *seg, int *curr_pos)
{
	char	*str;
	int		start;
	char	quote;

	start = *curr_pos;
	while (is_greatorless(seg[*curr_pos]) || is_space(seg[*curr_pos]))
		(*curr_pos)++;
	while (!is_greatorless(seg[*curr_pos])
		&& !is_space(seg[*curr_pos]) && seg[*curr_pos])
	{
		if (is_quote(seg[*curr_pos]))
		{
			quote = seg[*curr_pos];
			(*curr_pos)++;
			while (seg[*curr_pos] && seg[*curr_pos] != quote)
				(*curr_pos)++;
			if (seg[*curr_pos] == '\0')
				break ;
		}
		(*curr_pos)++;
	}
	str = ft_substr(seg, start, *curr_pos - start);
	add_str_to_array(red_array, str);
	free(str);
}

/*
**	Function: get_segment_cmd
**	---------------------------------
**	This function gets a command.
**	Then will be treated forward.

**	Parameters:
**		cmd_array:	pointer to the redirection array.
		seg:		the segment string.
		curr_pos:	current position of the segment string.

**	Return:
**		Non.
*/
void	get_segment_cmd(char ***cmd_array, char *seg, int *curr_pos)
{
	char	*str;
	int		start;
	char	quote;

	start = *curr_pos;
	quote = 0;
	while (!is_greatorless(seg[*curr_pos])
		&& !is_space(seg[*curr_pos]) && seg[*curr_pos])
	{
		if (is_quote(seg[*curr_pos]))
		{
			quote = seg[*curr_pos];
			(*curr_pos)++;
			while (seg[*curr_pos] && seg[*curr_pos] != quote)
				(*curr_pos)++;
			if (seg[*curr_pos] == '\0')
				break ;
		}
		(*curr_pos)++;
	}
	str = ft_substr(seg, start, *curr_pos - start);
	add_str_to_array(cmd_array, str);
	free(str);
}

/*
**	Function: get_segment_red
**	---------------------------------
**	This function gets the segment of the input string.
**	Then creates a new list with the content
**	needed to be trated after like the command array and the redirection array.

**	Parameters:
**		input_segment:	array.

**	Return:
**		t_list with a struct content.
*/
t_list	*get_segment(char *input_seg)
{
	t_seg	*new_seg;
	int		i;

	i = 0;
	new_seg = malloc(sizeof(t_seg));
	if (!new_seg)
		return (NULL);
	new_seg->cmd = NULL;
	new_seg->red = NULL;
	while (input_seg[i])
	{
		if (is_space(input_seg[i]))
			i++;
		else if (is_greatorless(input_seg[i]))
			get_segment_red(&new_seg->red, input_seg, &i);
		else
			get_segment_cmd(&new_seg->cmd, input_seg, &i);
	}
	return (ft_lstnew(new_seg));
}

/*
**	Function: parse
**	---------------------------------
**	This function parse the input line;

**	Parameters:
**		input:	input string from readline.

**	Return:
**		Non.
*/

void	parse(char *input)
{
	t_list	*head;
	char	**parse_input;
	int		i;

	parse_input = split_and_trim((find_and_replace(input, "|", 1)), 1);
	head = NULL;
	i = -1;
	while (parse_input[++i])
		ft_lstadd_back(&head, get_segment(parse_input[i]));
	parse_segments(head);
	shell()->segment_lst = head;
}
