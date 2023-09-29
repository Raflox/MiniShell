/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 13:17:41 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_word(char *seg, int *curr_pos, char *red)
{
	char	*str;
	char	quote;
	char	was_q;

	str = NULL;
	was_q = false;
	quote = 0;
	while (seg[*curr_pos] && !end_word(seg[*curr_pos], quote))
	{
		if (is_quote(seg[*curr_pos]) && !quote)
		{
			quote = seg[*curr_pos];
			was_q = true;
		}
		else if (is_quote(seg[*curr_pos]) && quote == seg[(*curr_pos)])
			quote = 0;
		else if ((!quote || (quote && quote == '"')) \
			&& seg[*curr_pos] == '$' && ft_strcmp(red, "<<") != 0)
			expand_variable(seg, &str, curr_pos);
		else
			add_c_to_string(&str, seg[*curr_pos]);
		(*curr_pos)++;
	}
	if (seg[*curr_pos] == '\0' && quote)
		display_error(1, "Minishell doesn't handle quotes", true);
	if (!str && was_q)
		str = ft_calloc(1, 1);
	return (str);
}

void	get_reds(t_list *lst)
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
				if (seg->std.in != -1 && !seg->heredoc)
					close(seg->std.in);
				if (access(&seg->red[i][1], F_OK))
				{
					seg->red_error = 1;
					break ;
				}
				if (!seg->heredoc)
				{
					seg->std.in = open(&seg->red[i][1], O_RDONLY);
					if (seg->std.in == -1)
					{
						seg->red_error = 1;
						break ;
					}
				}
			}
			else
			{
				if (seg->std.out != -1)
					close(seg->std.out);
				if (seg->red[i][0] == '>' && seg->red[i][1] == '>')
				{
					seg->std.out = open(&seg->red[i][2], O_RDWR | O_CREAT | O_APPEND, 0644);
					if (seg->std.out == -1)
					{
						seg->red_error = 1;
						break ;
					}
				}
				else if (seg->red[i][0] == '>' && seg->red[i][1] != '>')
				{
					seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
					if (seg->std.out == -1)
					{
						seg->red_error = 1;
						break ;
					}
				}
			}
		}
		if (seg->red_error == 1)
			display_error(1, strerror(errno), false);
		temp = temp->next;
	}
}

void	parse_util(char *input, t_list **head)
{
	char	**parse_input;
	int		i;

	parse_input = split_and_trim((find_and_replace(input, "|", 1)), 1);
	i = -1;
	while (parse_input[++i])
		ft_lstadd_back(head, get_segment(parse_input[i]));
	free_array(&parse_input);
	shell()->segment_lst = *head;
	init_built_in_flag(shell()->segment_lst);
}


int	parse(char *input)
{
	t_list	*head;

	head = NULL;
	if (pipe_sintax(input))
	{
		display_error(1, "Syntax Error", false);
		shell()->segment_lst = head;
		shell()->error = true;
		return (0);
	}
	parse_util(input, &head);
	if (!shell()->error)
	{
		if (get_heredoc(shell()->segment_lst))
		{
			shell()->error = true;
			return (0);
		}
		get_reds(shell()->segment_lst);
	}
	return (0);
}
