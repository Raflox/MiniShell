/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/20 16:39:54 by rgomes-c         ###   ########.fr       */
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
		{
			shell()->exit_code = 1;
			write(STDERR_FILENO, " No such file or directory\n", 27);
		}
		return (open(filename, O_RDONLY));
	}
	else if (mode == APPEND)
	{
		if (access(filename, W_OK))
		{
			shell()->exit_code = 1;
			write(STDERR_FILENO, " No such file or directory\n", 27);
		}
		return (open(filename, O_RDWR | O_CREAT | O_APPEND, 0644));
	}
	else
	{
		if (access(filename, W_OK))
		{
			shell()->exit_code = 1;
			write(STDERR_FILENO, " No such file or directory\n", 27);
		}
		return (open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644));
	}
	return (-2);
}

int	open_fds(t_seg *seg)
{
	int	i;
	int	in;
	int	out;

	if (seg->in || seg->here)
	{
		seg->dup_fd[0] = dup(STDIN_FILENO);
		if (seg->heredoc)
			in = heredoc(seg);
		else
		{
			if (seg->here)
				close(heredoc(seg));
			in = file_ctl(seg->in, INFILE);
		}
		if (in == -1)
			return (1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (seg->out)
	{
		i = -1;
		while (seg->out[++i])
		{
			if (seg->out[i + 1] == NULL && seg->append)
				out = file_ctl(seg->out[i], APPEND);
			else
				out = file_ctl(seg->out[i], OUTFILE);
			if (out < 0)
				return (1);
			if (seg->out[i + 1])
				close(out);
		}
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	return (0);
}

void	open_fds_2(t_seg *cmd)
{
	int	i;

	cmd->std.in = -1;
	cmd->std.out = -1;
	if (cmd->here || cmd->in)
	{
		if (cmd->heredoc)
			cmd->std.in = heredoc(cmd);
		else
		{
			close(heredoc(cmd));
			cmd->std.in = file_ctl(cmd->in, INFILE);
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
			i++;
		}
	}
}

void	process_ctl_2(t_list *curr, char **env)
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
			is_built_in(cmd->cmd);
		else
			execute(cmd->cmd, env);
		free_all();
		exit(shell()->exit_code);
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

void	process_ctl(t_list *curr, char **env)
{
	t_seg	*cmd;
	t_seg	*next = NULL;

	//cmd->dup_fd[0] = -1;
	//cmd->dup_fd[1] = -1;
	cmd = curr->content;
	if (curr->next)
		next = curr->next->content;
	if (next)
		pipe(next->pipe_fd);
	cmd->pid = fork();
	if (cmd->pid)
	{
		if (next)
			close(next->pipe_fd[1]);
		if (cmd->idx > 0)
			close(cmd->pipe_fd[0]);
	}
	else
	{
		open_fds_2(cmd);
		if (cmd->idx > 0)
		{
			cmd->dup_fd[0] = dup2(cmd->pipe_fd[0], STDIN_FILENO);
			close(cmd->pipe_fd[0]);
		}
		if (curr->next)
		{
			cmd->dup_fd[1] = dup2(next->pipe_fd[1], STDOUT_FILENO);
			close(next->pipe_fd[0]);
			close(next->pipe_fd[1]);
		}
		if (cmd->builtin)
			is_built_in(cmd->cmd);
		else
			execute(cmd->cmd, env);
		close(cmd->dup_fd[0]);
		close(cmd->dup_fd[1]);
		free_all();
		exit(shell()->exit_code);
	}
}

void	executeCommandList(t_list *seg_list)
{
	int		idx;
	int		status;
	t_list	*current;

	current = seg_list;
	while (current)
	{
		open_fds_2(current->content);
		current = current->next;
	}
	idx = 0;
	current = seg_list;
	while (current != NULL)
	{
		((t_seg *)current->content)->idx = idx++;
		//process_ctl(current, shell()->env);
		process_ctl_2(current, shell()->env);
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
