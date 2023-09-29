/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:24:56 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 12:55:55 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>

// void	init_seg(t_seg *seg)
// {
// 	seg->heredoc = false;
// 	seg->red_error = 0;
// 	seg->cmd = NULL;
// 	seg->red = NULL;
// 	seg->in = NULL;
// 	seg->out = NULL;
// 	seg->here = NULL;
// 	seg->append = false;
// 	seg->std.in = -1;
// 	seg->std.out = -1;
// }

// int	end_word(char c, char quote)
// {
// 	if ((is_greatorless(c) || is_space(c)) && !quote)
// 		return (1);
// 	return (0);
// }

// int	get_reds_in(t_seg *seg, int i)
// {
// 	if (seg->std.in != -1 && !seg->heredoc)
// 		close(seg->std.in);
// 	if (access(&seg->red[i][1], F_OK))
// 	{
// 		seg->red_error = 1;
// 		return (1);
// 	}
// 	if (!seg->heredoc)
// 	{
// 		seg->std.in = open(&seg->red[i][1], O_RDONLY);
// 		if (seg->std.in == -1)
// 		{
// 			seg->red_error = 1;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int	get_reds_out(t_seg *seg, int i)
// {
// 	if (seg->std.out != -1)
// 		close(seg->std.out);
// 	if (seg->red[i][0] == '>' && seg->red[i][1] == '>')
// 	{
// 		seg->std.out = open(&seg->red[i][2], O_RDWR | O_CREAT | O_APPEND, 0644);
// 		if (seg->std.out == -1)
// 		{
// 			seg->red_error = 1;
// 			return (1);
// 		}
// 	}
// 	else if (seg->red[i][0] == '>' && seg->red[i][1] != '>')
// 	{
// 		seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
// 		if (seg->std.out == -1)
// 		{
// 			seg->red_error = 1;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// void	get_reds(t_list *lst)
// {
// 	t_list	*temp;
// 	t_seg	*seg;
// 	int		i;

// 	temp = lst;
// 	while (temp)
// 	{
// 		seg = (t_seg *)temp->content;
// 		i = -1;
// 		while (seg->red && seg->red[++i])
// 		{
// 			if (seg->red[i][0] == '<' && seg->red[i][1] != '<')
// 			{
// 				if (get_reds_in(seg, i))
// 					break ;
// 			}
// 			else if (get_reds_out(seg, i))
// 				break ;
// 		}
// 		if (seg->red_error == 1)
// 			display_error(1, strerror(errno), false);
// 		temp = temp->next;
// 	}
// }
