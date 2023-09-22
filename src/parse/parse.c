/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/22 20:43:39 by parallels        ###   ########.fr       */
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


void	init_seg(t_seg *seg)
{
	seg->heredoc = false;
	seg->red_error = 0;
	seg->cmd = NULL;
	seg->red = NULL;
	seg->in = NULL;
	seg->out = NULL;
	seg->here = NULL;
	seg->append = false;
	seg->std.in = -1;
	seg->std.out = -1;
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
	new_seg->builtin = false;
	init_seg(new_seg);
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

void	get_heredoc(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		i = -1;
		while (seg->red && seg->red[++i])
		{
			if (seg->red[i][0] == '<' && seg->red[i][1] == '<')
			{
				add_str_to_array(&seg->here, &seg->red[i][2]);
				if (seg->red[i + 1] == NULL)
					seg->heredoc = true;
			}
		}
		temp = temp->next;
	}
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
		i = -1;
		while (seg->red && seg->red[++i])
		{
			if (seg->red[i][0] == '<' && seg->red[i][1] != '<')
			{
				if (seg->std.in != -1)
					close(seg->std.in);
				if (access(&seg->red[i][1], F_OK))
				{
					write(STDERR_FILENO, &seg->red[i][1], ft_strlen(&seg->red[i][1]));
					seg->red_error = 1;
					break ;
				}
				seg->std.in = open(&seg->red[i][1], O_RDONLY);
			}
			else
			{
				if (seg->red[i][0] == '>' && seg->red[i][1] == '>')
				{
					if (seg->std.out != -1)
						close(seg->std.out);
					if (access(&seg->red[i][2], W_OK))
					{
						write(STDERR_FILENO, &seg->red[i][2], ft_strlen(&seg->red[i][2]));
						seg->red_error = 1;
						break ;
					}
					seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_APPEND, 0644);
				}
				else if (seg->red[i][0] == '>' && seg->red[i][1] != '>')
				{
					if (seg->std.out != -1)
						close(seg->std.out);
					if (access(&seg->red[i][1], W_OK))
					{
						printf("%s\n", seg->red[i]);
						write(STDERR_FILENO, &seg->red[i][1], ft_strlen(&seg->red[i][1]));
						seg->red_error = 1;
						break ;
					}
					seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
				}
			}
		}
		if (seg->red_error == 1)
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
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

void	parse(char *input)
{
	t_list	*head;
	char	**parse_input;
	int		i;

	shell()->error = false;
	parse_input = split_and_trim((find_and_replace(input, "|", 1)), 1);
	//print_array(parse_input);
	head = NULL;
	i = -1;
	while (parse_input[++i])
		ft_lstadd_back(&head, get_segment(parse_input[i]));
	free_array(&parse_input);
	parse_segments(head);
	shell()->segment_lst = head;
	//print_array(((t_seg *)shell()->segment_lst->content)->cmd);
	get_real_red(shell()->segment_lst);
	init_built_in_flag(shell()->segment_lst);
}
