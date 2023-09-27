/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:29:16 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/26 17:51:56 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

§§§§§§§§§§§§
int	heredoc(t_seg *cmd)
{
	char	*line;
	int		pipe_fd[2];
	int		i;

	signal(SIGQUIT, SIG_IGN);
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
			if (!line)
			{
				heredoc_error(cmd->here[i]);
				return 1;
			}
			if (line[0] != EOF)
			{
				if (!(ft_strncmp(line, cmd->here[i], ft_strlen(cmd->here[i]))))
					break ;
				if (cmd->here[i + 1] == NULL)
					write(pipe_fd[1], line, ft_strlen(line));
				free(line);
				line = NULL;
			}
		}
		i++;
	}
	handle_signals();
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
