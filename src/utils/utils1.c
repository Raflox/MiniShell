/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:16:02 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_seg(void)
{
	t_list	*temp;
	t_list	*next;
	t_seg	*seg;

	temp = shell()->segment_lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		if (seg->cmd)
			free_array(&seg->cmd);
		if (seg->red)
			free_array(&seg->red);
		if (seg->in)
			free(seg->in);
		if (seg->out)
			free_array(&seg->out);
		if (seg->out)
			free_array(&seg->here);
		next = temp->next;
		free(seg);
		free(temp);
		temp = next;
	}
}

void	free_all(void)
{
	if (shell()->env)
		free_array(&shell()->env);
	if (shell()->export)
		free_array(&shell()->export);
	if (shell()->pwd)
		free(shell()->pwd);
	free_seg();
}

