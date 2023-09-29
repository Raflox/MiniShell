/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:29:16 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 09:39:27 by rafilipe         ###   ########.fr       */
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
	shell()->error = true;
	exit(EXIT_FAILURE);
}

void	heredoc_expand_variable(char **line)
{
	char	*temp;
	int		i;

	temp = NULL;
	if (!(*line))
		return ;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			expand_variable(*line, &temp, &i);
		else
			add_c_to_string(&temp, (*line)[i]);
		i++;
	}
	free(*line);
	*line = temp;
}

int	heredoc(t_seg *cmd)
{
	char	*line;
	pid_t	pid;
	int		i;

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
				add_c_to_string(&cmd->here[i], 10);
				if (!(ft_strcmp(line, cmd->here[i])))
				{
					free(line);
					break ;
				}
				rm_last_c_from_str(&cmd->here[i]);
				if (cmd->here[i + 1] == NULL)
				{
					heredoc_expand_variable(&line);
					write(shell()->here_fd[1], line, ft_strlen(line));
				}
				free(line);
				line = NULL;
			}
			i++;
		}
		handle_signals();
		close(shell()->here_fd[1]);
		close (shell()->here_fd[0]);
		free_all(1, 1, 1, 0);
		exit(0);
	}
	close(shell()->here_fd[1]);
	wait(&pid);
	shell()->in_heredoc = false;
	return (shell()->here_fd[0]);
}
