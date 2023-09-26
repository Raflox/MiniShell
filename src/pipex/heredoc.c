/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:29:16 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/26 18:40:32 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_error(char *str)
{
	printf("\nWarning: heredoc on line 1 delimited by EOF (wanted: \"%s\")\n", str);
	handle_signals();
}

void	sig_here(int a)
{
	(void)a;
	free_all(1, 1, 1, 0);
	close(shell()->here_fd[0]);
	close(shell()->here_fd[1]);
	exit(EXIT_FAILURE);
}

int	heredoc(t_seg *cmd)
{
	char	*line;
	pid_t	pid;
	int		i;

	shell()->here_fd[0] = -1;
	shell()->here_fd[1] = -1;
	shell()->in_heredoc = true;
	if (pipe(shell()->here_fd) < 0)
		perror("");
	pid = fork();
	i = 0;
	line = NULL;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_here);
		while (cmd->here && cmd->here[i])
		{
			while (true)
			{
				write(0, "> ", 2);
				line = get_next_line(0);
				if (!line)
				{
					heredoc_error(cmd->here[i]);
					close(shell()->here_fd[1]);
					close(shell()->here_fd[0]);
					free_all(1, 1, 1, 0);
					exit(-1);
				}
				if (!(ft_strncmp(line, cmd->here[i], ft_strlen(cmd->here[i]))))
					break ;
				if (cmd->here[i + 1] == NULL)
					write(shell()->here_fd[1], line, ft_strlen(line));
				free(line);
				line = NULL;
			}
			i++;
		}
		if (line)
			free(line);
		handle_signals();
		close(shell()->here_fd[1]);
		close (shell()->here_fd[0]);
		free_all(1, 1, 1, 0);
		exit(0);
	}
	close(shell()->here_fd[1]);
	wait(0);
	shell()->in_heredoc = false;
	return (shell()->here_fd[0]);
}
