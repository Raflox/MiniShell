/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/04 21:16:51 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO: Create function to get last outfile from matrix.

typedef struct s_cmd
{
	char	*cmd;
	char	*infile;
	char	*outfile;
	char	**env;
}	t_cmd;

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
	return (open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

void	simple_cmd(t_cmd cmd_struct)
{
	int		in_fd;
	int		out_fd;
	char	*cmd;
	int		pid;

/* 	if (ac == 2)
		execute(av[1], env); */
	if (*cmd_struct.infile)
	{
		in_fd = file_ctl(cmd_struct.infile, INFILE);
		dup2(in_fd, STDIN_FILENO);
	}
	if (*cmd_struct.outfile)
	{
		out_fd = file_ctl(cmd_struct.outfile, OUTFILE);
		dup2(out_fd, STDOUT_FILENO);
	}
	pid = fork();
	if (pid == 0)
		execute(cmd_struct.cmd, cmd_struct.env);
	close(in_fd);
	close(out_fd);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	cmd_struct;

	cmd_struct.cmd = "grep rafael";
	cmd_struct.infile = "test.txt";
	cmd_struct.outfile = "outfile";
	cmd_struct.env = env;

	simple_cmd(cmd_struct);
}