/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:29:16 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 11:01:45 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	close_here_yes(int e_code)
{
	close(shell()->here_fd[1]);
	close(shell()->here_fd[0]);
	free_all(1, 1, 1, 0);
	exit(e_code);
}

int	do_while(t_seg *cmd, int i)
{
	char	*line;

	line = NULL;
	write(0, "> ", 2);
	line = get_next_line(0);
	if (!line)
	{
		heredoc_error(cmd->here[i]);
		close_here_yes(-1);
	}
	add_c_to_string(&cmd->here[i], 10);
	if (!(ft_strcmp(line, cmd->here[i])))
	{
		free(line);
		return (1);
	}
	rm_last_c_from_str(&cmd->here[i]);
	if (cmd->here[i + 1] == NULL)
	{
		heredoc_expand_variable(&line);
		write(shell()->here_fd[1], line, ft_strlen(line));
	}
	free(line);
	return (0);
}

int	heredoc(t_seg *cmd)
{
	pid_t	pid;
	int		i;

	shell()->in_heredoc = true;
	if (pipe(shell()->here_fd) < 0)
		perror("");
	pid = fork();
	i = -1;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_here);
		while (cmd->here && cmd->here[++i])
		{
			while (!do_while(cmd, i))
				continue ;
		}
		handle_signals();
		close_here_yes(1);
	}
	close(shell()->here_fd[1]);
	wait(&pid);
	shell()->in_heredoc = false;
	return (shell()->here_fd[0]);
}
