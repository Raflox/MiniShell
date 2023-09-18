/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/18 22:57:17 by rgomes-c         ###   ########.fr       */
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
	return (ft_lstnew((t_seg *)new_seg));
}

//TODO verificar o tamanho das funções
void	get_real_red(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		seg->in = NULL;
		seg->here = NULL;
		seg->append = false;
		seg->heredoc = false;
		seg->out = NULL;
		i = -1;
		while (seg->red && seg->red[++i])
		{
			if (seg->red[i][0] == '<')
			{
				if (seg->red[i][1] == '<')
				{
					add_str_to_array(&seg->here, &seg->red[i][2]);
					if (seg->red[i + 1] == NULL)
						seg->heredoc = true;
				}
				else
					seg->in = ft_strdup(&seg->red[i][1]);
			}
			else
			{
				if (seg->red[i][1] == '>')
				{
					add_str_to_array(&seg->out, &seg->red[i][2]);
					if (seg->red[i + 1] == NULL)
						seg->append = true;
				}
				else
					add_str_to_array(&seg->out, &seg->red[i][1]);
			}
		}
		temp = temp->next;
	}
}

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "export") == 0 || ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	init_built_in_flag(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		seg->builtin = false;
		i = -1;
		while (seg->cmd && seg->cmd[++i])
		{
			if (is_builtin(seg->cmd[i]))
				seg->builtin = true;
		}
		temp = temp->next;
	}
}

// void	parse_checker(t_list *lst)
// {
// 	t_list	*temp;
// 	t_seg	*seg;
// 	//int		i;

// 	temp = lst;
// 	while (temp)
// 	{
// 		seg = temp->content;
// 		if (!seg->cmd || !seg->red)
// 			shell()->error = true;
// 		if (seg->cmd)
// 		{
// 			printf("existe e bem");
// 		}
// 		temp = temp->next;
// 	}
// }

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

	shell()->error = false;
	parse_input = split_and_trim((find_and_replace(input, "|", 1)), 1);
	head = NULL;
	i = -1;
	while (parse_input[++i])
		ft_lstadd_back(&head, get_segment(parse_input[i]));
	free_array(&parse_input);
	parse_segments(head);
	shell()->segment_lst = head;
	get_real_red(shell()->segment_lst);
	init_built_in_flag(shell()->segment_lst);
	//parse_checker(shell()->segment_lst);
}
