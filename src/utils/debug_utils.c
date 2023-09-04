/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:39:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 14:41:13 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_lst(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		printf("segment -----------------------------\n");
		seg = (t_seg *)temp->content;
		i = -1;
		while (seg->cmd && seg->cmd[++i])
			printf("cmd_arg[%d] - %s\n", i, seg->cmd[i]);
		i = -1;
		while (seg->red && seg->red[++i])
			printf("red_arg[%d] - %s\n", i, seg->red[i]);
		temp = temp->next;
	}
}
