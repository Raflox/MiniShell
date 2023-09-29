/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:36:08 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 13:09:51 by rafilipe         ###   ########.fr       */
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
