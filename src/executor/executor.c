/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/15 11:56:29 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: Create function to get last outfile from matrix.
//TODO: Create all outfiles, but only write to last.

void	process_ctl(t_list *curr, char **env)
{
	t_seg*	cmd;
	t_seg*	next = NULL;

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
		execute(cmd->cmd, env);
		close(cmd->dup_fd[0]);
		close(cmd->dup_fd[1]);
		exit(shell()->exit_code);
	}
}

int	file_ctl(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			error("acesss file");
		}
		return (open(filename, O_RDONLY));
	}
	if (mode == APPEND)
		return (open(filename, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

void executeCommand(t_seg *seg)
{
	(void)seg;
/*     if (seg->in) {
        in_fd = file_ctl(seg->in, INFILE);
        dup2(in_fd, STDIN_FILENO);
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
	} */
}

void executeCommandList(t_list *seg_list)
{
	int idx = 0;
	int	status;
    t_list *current = seg_list;

    while (current != NULL)
	{
		((t_seg*)current->content)->idx = idx++;
		//fprintf(stderr, "AQUI\n");
		//fprintf(stderr, "CMD::%s\n", ((t_seg *)current->content)->cmd[0]);
        //executeCommand(current);
        process_ctl(current, shell()->env);
		
		current = current->next;
    }
	current = seg_list;
	while (current)
	{
		waitpid(((t_seg*)current->content)->pid, &status, 0);
		current = current->next;
	}
	if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
}

/* int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
} */