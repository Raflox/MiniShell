/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/04 18:29:55 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	execute(cmd_struct.cmd, cmd_struct.env);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	cmd_struct;

	cmd_struct.cmd = "grep OBJS";
	cmd_struct.infile = "Makefile";
	cmd_struct.outfile = "outfile";
	cmd_struct.env = env;

	simple_cmd(cmd_struct);
}