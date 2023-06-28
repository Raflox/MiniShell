/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 09:39:12 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//seg de segmento
t_list	*lst(void)
{
	static t_list	lst;

	return (&lst);
}

void	exit_program(char *error, int code)
{
	(void)code;
	printf("Error: %s\n", error);
	//exit(code);
}

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
// void	expand_variable(char *input_piece, char **new_piece, int *curr_pos)
// {
// 	int	start;

// 	if (input_piece[*curr_pos + 1] == '?')
// 		return ;
// 	if (input_piece[*curr_pos + 1] == ' ')
// 		return ;
// 	(*curr_pos)++;
// 	start = *curr_pos;
// 	while (input_piece[*curr_pos] && input_piece[*curr_pos] != ' '
// 		&& !is_quote(input_piece[*curr_pos]))
// 		(*curr_pos)++;
// 	if (start != *curr_pos)
// 		add_char_to_string(new_piece, '\\');
// 	else
// 		exit_program("error expanding variable", 0);
// }

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
// void	skip_quote(char *input_piece, char **new_piece,
// 	char quote, int *curr_pos)
// {
// 	while (input_piece[++(*curr_pos)])
// 	{
// 		if (quote == '\"' && input_piece[*curr_pos] == '$')
// 			expand_variable(input_piece, new_piece, curr_pos);
// 		if (input_piece[*curr_pos] == quote)
// 		{
// 			(*curr_pos)++;
// 			return ;
// 		}
// 		if (input_piece[*curr_pos + 1] == '\0')
// 			exit_program("aquasdi nas quotes", 0);
// 		else
// 			add_char_to_string(new_piece, input_piece[*curr_pos]);
// 	}
// }

void	new_redirection(char ***red_array, char *seg, int *curr_pos)
{
	char	*str;
	int		start;
	char	quote;

	start = *curr_pos;
	while (is_greatorless(seg[*curr_pos]) || is_space(seg[*curr_pos]))
		(*curr_pos)++;
	while (!is_greatorless(seg[*curr_pos]) && !is_space(seg[*curr_pos]) && seg[*curr_pos])
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
**	Function: get_command
**	---------------------------------
**	This function get the command from the input only.
**	Then will be treated forward.

**	Parameters:
**		input:		input_piece.
					current_position.

**	Return:
**		Non.
*/
void	new_command(char ***cmd_array, char *seg, int *curr_pos)
{
	char	*str;
	int		start;
	char	quote;

	start = *curr_pos;
	quote = 0;
	while (!is_greatorless(seg[*curr_pos]) && !is_space(seg[*curr_pos]) && seg[*curr_pos])
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

t_list	*new_segment(char *input_seg)
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
			new_redirection(&new_seg->red, input_seg, &i);
		else
			new_command(&new_seg->cmd, input_seg, &i);
	}
	return (ft_lstnew(new_seg));
}

void	print_lst(t_list *lst)
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
			printf("arg[%d] - %s\n", i, seg->cmd[i]);
		i = -1;
		while (seg->red && seg->red[++i])
			printf("arg[%d] - %s\n", i, seg->red[i]);
		temp = temp->next;
	}
}

void	parse(char *input)
{
	t_list	*head;
	char	**parse_input;
	int		i;

	parse_input = split_and_trim((find_and_replace(input, "|", 1)), 1);
	head = NULL;
	i = -1;
	while (parse_input[++i])
		ft_lstadd_back(&head, new_segment(parse_input[i]));
	print_lst(head);
}
