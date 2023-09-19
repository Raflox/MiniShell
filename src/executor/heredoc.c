/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:44:23 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/15 10:46:15 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_seg *cmd)
{
	char	*line;
	int		pipe_fd[2];
	int		i;

	if (pipe(pipe_fd) < 0)
		perror("");
	i = 0;
	line = NULL; 
	while (cmd->here[i])
	{
		while (true)
		{
			write(0, ">", 1);
			line = get_next_line(0);
			if (!(ft_strncmp(line, cmd->here[i], ft_strlen(cmd->here[i]))))
				break ;
			if (cmd->here[i + 1] == NULL)
				write(pipe_fd[0], line, ft_strlen(line));
			free(line);
			line = NULL;
		}
		i++;
	}
	return (pipe_fd[0]);
}
