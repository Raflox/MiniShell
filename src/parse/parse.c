/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 12:55:30 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	end_word(char c, char quote)
{
	if ((is_greatorless(c) || is_space(c)) && !quote)
		return (1);
	return (0);
}

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

char	*parse_red(char *seg, int *curr_pos)
{
	char	*red;
	char	*temp;
	char	*final;

	red = NULL;
	temp = NULL;
	final = NULL;
	add_c_to_string(&red, seg[(*curr_pos)++]);
	if (seg[(*curr_pos) - 1] == seg[(*curr_pos)])
		add_c_to_string(&red, seg[(*curr_pos)++]);
	while (seg[(*curr_pos)] && is_space(seg[*curr_pos]))
		(*curr_pos)++;
	if (seg[(*curr_pos)] && !is_greatorless(seg[(*curr_pos)]))
	{
		temp = parse_word(seg, curr_pos, red);
		if (temp)
		{
			final = ft_strjoin(red, temp);
			free(temp);
		}
	}
	else
		display_error(1, "Syntax Error", true);
	free(red);
	return (final);
}

t_list	*get_segment(char *input_seg)
{
	char	*temp;
	t_seg	*new_seg;
	int		i;

	i = 0;
	new_seg = malloc(sizeof(t_seg));
	if (!new_seg)
		return (NULL);
	new_seg->builtin = false;
	init_seg(new_seg);
	while (input_seg[i] && !shell()->error)
	{
		if (is_space(input_seg[i]))
			i++;
		else if (is_greatorless(input_seg[i]))
		{
			temp = parse_red(input_seg, &i);
			if (temp)
			{
				add_str_to_array(&new_seg->red, temp);
				free(temp);
			}
		}
		else
		{
			temp = parse_word(input_seg, &i, NULL);
			if (temp)
			{
				add_str_to_array(&new_seg->cmd, temp);
				free(temp);
			}
		}
	}
	return (ft_lstnew((t_seg *)new_seg));
}

int	get_heredoc(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		i = -1;
		seg->heredoc = false;
		while (seg->red && seg->red[++i])
		{
			if (seg->red[i][0] == '<' && seg->red[i][1] == '<')
			{
				add_str_to_array(&seg->here, &seg->red[i][2]);
				seg->heredoc = true;
			}
			else if (seg->red[i][0] == '<')
				seg->heredoc = false;
		}
		if (seg->here && seg->heredoc)
		{
			seg->std.in = heredoc(seg);
			if (seg->std.in == -1)
				return (1);
		}
		else if (seg->here)
		{
			if (close(heredoc(seg)) == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

//TODO verificar o tamanho das funções
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

int	parse(char *input)
{
	t_list	*head;
	char	**parse_input;
	int		i;

	head = NULL;
	if (pipe_sintax(input))
	{
		display_error(1, "Syntax Error", false);
		shell()->segment_lst = head;
		shell()->error = true;
		return (0);
	}
	parse_input = split_and_trim((find_and_replace(input, "|", 1)), 1);
	i = -1;
	while (parse_input[++i])
		ft_lstadd_back(&head, get_segment(parse_input[i]));
	free_array(&parse_input);
	shell()->segment_lst = head;
	init_built_in_flag(shell()->segment_lst);
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
