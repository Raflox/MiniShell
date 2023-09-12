/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/11 16:33:11 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO: Create function to get last outfile from matrix.
//TODO: Create all outfiles, but only write to last.

void	process_ctl(char *cmd, char **env, int flag)
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
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (flag == 0)
			exit(1);
		else
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
	//char	*cmd;
	//int		pid;
	int		i;

	i = 0;
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
	if (seg->builtin)
		printf("AQUI\n"); // run builtin function
/* 	process_ctl(av[2], env, fd[0]); // Redirect and execute the first command.
	// FIXME: ADD CONDITION HERE TO VERIFY IF THERE IS MORE THAN ONE COMMAND TO BE EXECUTED
	while (i < ac - 2) //alterar iteração para listas
	{
		fprintf(stderr, "arg:%d\n", i);
		process_ctl(av[i++], env, 1); // Loop to redirect and execute subsequent commands.
	}
	execute(av[i], env); // Execute the final command. */
	close(in_fd);
	close(out_fd);
}

void	seg_handler(t_sh cmd_struct)
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
	t_cmd	cmd_struct;

	cmd_struct.cmd = "grep rafael";
	cmd_struct.infile = "test.txt";
	cmd_struct.outfile = "outfile";
	cmd_struct.env = env;
	cmd_struct.is_built_in = true;
	cmd_struct.red_type = "append";

	simple_cmd(cmd_struct);
} */