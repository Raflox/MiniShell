/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/27 12:04:56 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		{
			dup2(cmd->std.in, STDIN_FILENO);
			close(cmd->std.in);
		}
		close(cmd->pipe_fd[0]);
		if (cmd->std.out != -1)
		{
			dup2(cmd->std.out, STDOUT_FILENO);
			close(cmd->std.out);
		}
		else if (next && next->cmd)
			dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[1]);
		if (cmd->red_error != 1)
		{
			if (cmd && cmd->builtin)
				execute_builtin(cmd->cmd, cmd->red_error);
			else if (cmd->cmd)
				execute(cmd->cmd, env);
		}
		free_all(1, 1, 1, 0);
		exit(shell()->exit_code);
	}
	else
	{
		if (next && next->cmd && next->std.in == -1)
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

	status = 0;
	current = seg_list;
	while (current != NULL)
	{
		if (!current->next && ((t_seg *)current->content)->red_error)
			shell()->exit_code = 1;
		process_ctl(current, shell()->env);
		current = current->next;
	}
	current = seg_list;
	while (current != NULL)
	{
		waitpid(((t_seg *)current->content)->pid, &status, 0);
		current = current->next;
	}
	if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
}
