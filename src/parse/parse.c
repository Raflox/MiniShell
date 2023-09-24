/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/24 22:19:42 by parallels        ###   ########.fr       */
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

char	*parse_word(char *seg, int *curr_pos)
{
	char	*str;
	char	quote;

	str = NULL;
	quote = 0;
	while (seg[*curr_pos] && !end_word(seg[*curr_pos], quote))
	{
		if (is_quote(seg[*curr_pos]) && !quote)
			quote = seg[*curr_pos];
		else if (is_quote(seg[*curr_pos]) && quote == seg[(*curr_pos)])
			quote = 0;
		else if ((!quote || (quote && quote == '"')) && seg[*curr_pos] == '$')
			expand_variable(seg, &str, curr_pos);
		else
			add_c_to_string(&str, seg[*curr_pos]);
		(*curr_pos)++;
	}
	if (seg[*curr_pos] == '\0' && quote)
		printf("nao da handle as quotes\n");
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
		temp = parse_word(seg, curr_pos);
		if (temp)
		{
			final = ft_strjoin(red, temp);
			free(temp);
		}
	}
	else
		printf("grande erro nas reds\n");
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
	while (input_seg[i])
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
			temp = parse_word(input_seg, &i);
			if (temp)
			{
				add_str_to_array(&new_seg->cmd, temp);
				free(temp);
			}
		}
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
					seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_APPEND, 0644);
				}
				else if (seg->red[i][0] == '>' && seg->red[i][1] != '>')
				{
					if (seg->std.out != -1)
						close(seg->std.out);
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

void	run_away(char *str)
{
	printf("run_away: %s\n", str);
	shell()->error = true;
}

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
	//parse_segments(head);
	shell()->segment_lst = head;
	init_built_in_flag(shell()->segment_lst);
	get_heredoc(shell()->segment_lst);
	get_reds(shell()->segment_lst);
}
