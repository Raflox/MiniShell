/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/12 19:10:15 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: Create function to get last outfile from matrix.
//TODO: Create all outfiles, but only write to last.

void	process_ctl(char **cmd, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		//waitpid(pid, NULL, 0);
	}
	else
	{
		printf("AQUI\n");
		printf("CMD 0 = %s\n", cmd[0]);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execute(cmd, env);
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

void	executor(t_seg *seg)
{
	int		in_fd;
	int		out_fd;
	int		i;
	int		pid;

	i = 0;
	in_fd = 0;
	out_fd = 0;
	if (seg->in) //get infile from first element of list
	{
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
	}
/* 	if (seg->builtin)
		printf("AQUI\n"); */ //is_built_in(seg->cmd);
	//process_ctl(seg->cmd, shell()->env); // Redirect and execute the first command.
	//seg_handler(seg);
	// FIXME: ADD CONDITION HERE TO VERIFY IF THERE IS MORE THAN ONE COMMAND TO BE EXECUTED
	/* while (i < ac - 2) //alterar iteração para listas
	{
		fprintf(stderr, "arg:%d\n", i);
		process_ctl(av[i++], env, 1); // Loop to redirect and execute subsequent commands.
	} */
	pid = fork();
	if (!pid)
		execute(seg->cmd, shell()->env); // Execute the final command.
	if (in_fd)
		close(in_fd);
	if (out_fd)
		close(out_fd);
}

void	seg_handler(t_sh *cmd_struct)
{
	t_list	*pipe_seg;

	pipe_seg = cmd_struct.segment_lst;
	while (pipe_seg != NULL)
	{
		executor((t_seg *)pipe_seg->content);
		pipe_seg = pipe_seg->next;
	}
}

/* int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
} */