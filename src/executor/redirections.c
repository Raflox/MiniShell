/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:05 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/15 12:00:19 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_reds(t_seg *seg)
{	
	if (seg->in) 
	{
       seg->main_fd[0] = file_ctl(seg->in, INFILE);
    }

	if (seg->out) //get outfile from last element of list
	{
		while (seg->out[i])
		{
			if (seg->append)
				out_fd = file_ctl(seg->out[i], APPEND);
			else
				out_fd = file_ctl(seg->out[i], OUTFILE);
			if (!seg->out[i + 1])
				dup2(out_fd, STDOUT_FILENO);
		}
	}
}