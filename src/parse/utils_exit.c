/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:49:20 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 14:50:31 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_lst_content(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		free_array(seg->cmd);
		if (seg->cmd)
			printf("existe sim\n");
		free_array(seg->red);
		temp = temp->next;
	}
}

void	readline_error(char *error, int code, bool need_free)
{
	(void)code;
	shell()->error = true;
	printf("Error: %s\n", error);
	if (need_free)
		free_lst_content(shell()->segment_lst);
	//exit(code);
}
