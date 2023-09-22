/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/22 12:19:51 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: Create function to get last outfile from matrix.
//TODO: Create all outfiles, but only write to last.

int	file_ctl(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
			write(STDERR_FILENO, " No such file or directory\n", 27);
		return (open(filename, O_RDONLY));
	}
	else if (mode == APPEND)
	{
		if (access(filename, W_OK))
			write(STDERR_FILENO, " Permission denied\n", 19);
		return (open(filename, O_RDWR | O_CREAT | O_APPEND, 0644));
	}
	else
	{
		if (access(filename, W_OK))
			write(STDERR_FILENO, " Permission denied\n", 19);
		return (open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644));
	}
}
void	open_reds(t_seg *cmd)
{
	int	i;

	cmd->std.in = -1;
	cmd->std.out = -1;
	cmd->red_error = 0;
	if (cmd->here || cmd->in)
	{
		if (cmd->heredoc)
			cmd->std.in = heredoc(cmd);
		else
		{
			close(heredoc(cmd));
			i = 0;
			while (cmd->in[i])
			{
				cmd->std.in = file_ctl(cmd->in[i], INFILE);
				if (cmd->in[i + 1])
					close(cmd->std.in);
				if (cmd->std.in == -1)
				{
					cmd->red_error = 1;
					break ;
				}
				i++;
			}
		}
	}
	if (cmd->out)
	{
		i = 0;
		while (cmd->out[i])
		{
			if (cmd->append)
				cmd->std.out = file_ctl(cmd->out[i], APPEND);
			else
				cmd->std.out = file_ctl(cmd->out[i], OUTFILE);
			if (cmd->out[i + 1])
				close(cmd->std.out);
			if (cmd->std.out == -1)
			{
				cmd->red_error = 1;
				break ;
			}
			i++;
		}
	}
}

void	process_ctl(t_list *curr, char **env)
{
	t_seg	*cmd;
	t_seg	*next;

	cmd = curr->content;
	next = NULL;
	if (curr->next)
		next = curr->next->content;
	pipe(cmd->pipe_fd);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->std.in != -1)
			dup2(cmd->std.in, STDIN_FILENO);
		close(cmd->pipe_fd[0]);
		if (cmd->std.out != -1)
		{
			dup2(cmd->std.out, STDOUT_FILENO);
			close(cmd->std.out);
		}
		else if (next && next->cmd)
			dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[1]);
		if (cmd->builtin)
			execute_builtin(cmd->cmd, cmd->red_error);
		else
			execute(cmd->cmd, env);
		free_all(true, true, true, true);
	}
	else
	{
		if (next && next->cmd && !next->in)
			next->std.in = dup(cmd->pipe_fd[0]);
		if (cmd->std.in != -1)
			close(cmd->std.in);
		if (cmd->std.out != -1)
			close(cmd->std.out);
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
}

void	executeCommandList(t_list *seg_list)
{
	int		status;
	t_list	*current;

	current = seg_list;
	while (current != NULL)
	{
		if (!((t_seg *)current->content)->red_error)
			process_ctl(current, shell()->env);
		if (!current->next && ((t_seg *)current->content)->red_error)
			shell()->exit_code = 1;
		current = current->next;
	}
	current = seg_list;
	while (current)
	{
		waitpid(((t_seg *)current->content)->pid, &status, 0);
		current = current->next;
	}
	if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
}
