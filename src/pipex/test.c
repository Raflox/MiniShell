/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:12:06 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/27 11:12:08 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int	heredoc(t_seg *cmd)
{
	char	*line;
	int		pipe_fd[2];
	int		i;

	//signals_here(0);
	if (pipe(pipe_fd) < 0)
		perror("");
	i = 0;
	line = NULL; 
	while (cmd->here && cmd->here[i])
	{
		while (true)
		{
			write(0, ">", 1);
			line = get_next_line(0);
			if (!(ft_strncmp(line, cmd->here[i], ft_strlen(cmd->here[i]))))
				break ;
			if (cmd->here[i + 1] == NULL)
				write(pipe_fd[1], line, ft_strlen(line));
			free(line);
			line = NULL;
		}
		i++;
	}
	if (line)
		free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);