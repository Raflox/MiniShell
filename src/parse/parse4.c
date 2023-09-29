/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:36:08 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 13:23:09 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_heredoc_2(t_seg *seg)
{
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
	return (0);
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
		if (get_heredoc_2(seg))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	get_reds_in(t_seg *seg, int i)
{
	if (seg->std.in != -1 && !seg->heredoc)
		close(seg->std.in);
	if (access(&seg->red[i][1], F_OK))
	{
		seg->red_error = 1;
		return (1);
	}
	if (!seg->heredoc)
	{
		seg->std.in = open(&seg->red[i][1], O_RDONLY);
		if (seg->std.in == -1)
		{
			seg->red_error = 1;
			return (1);
		}
	}
	return (0);
}

int	get_reds_out(t_seg *seg, int i)
{
	if (seg->std.out != -1)
		close(seg->std.out);
	if (seg->red[i][0] == '>' && seg->red[i][1] == '>')
	{
		seg->std.out = open(&seg->red[i][2], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (seg->std.out == -1)
		{
			seg->red_error = 1;
			return (1);
		}
	}
	else if (seg->red[i][0] == '>' && seg->red[i][1] != '>')
	{
		seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (seg->std.out == -1)
		{
			seg->red_error = 1;
			return (1);
		}
	}
	return (0);
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
				if (get_reds_in(seg, i))
					break ;
			}
			else if (get_reds_out(seg, i))
				break ;
		}
		if (seg->red_error == 1)
			display_error(1, strerror(errno), false);
		temp = temp->next;
	}
}
