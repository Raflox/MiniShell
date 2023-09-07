/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/07 12:34:33 by rafilipe         ###   ########.fr       */
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
	char	*red_type;
	bool	is_built_in;
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
	if (mode == APPEND)
		open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

void	simple_cmd(t_cmd cmd_struct)
{
	int		in_fd;
	int		out_fd;
	char	*cmd;
	int		pid;

	if (*cmd_struct.infile) //get infile from first element of list
	{
		in_fd = file_ctl(cmd_struct.infile, INFILE);
		dup2(in_fd, STDIN_FILENO);
	}
	if (*cmd_struct.outfile) //get outfile from last element of list
	{
		if (cmd_struct.red_type == "append")
			out_fd = file_ctl(cmd_struct.outfile, APPEND);
		out_fd = file_ctl(cmd_struct.outfile, OUTFILE);
		dup2(out_fd, STDOUT_FILENO);
	}
	if (cmd_struct.is_built_in)
		printf("AQUI\n"); // run builtin function
	process_ctl(av[2], env, fd[0]); // Redirect and execute the first command.
	// FIXME: ADD CONDITION HERE TO VERIFY IF THERE IS MORE THAN ONE COMMAND TO BE EXECUTED
	while (i < ac - 2) //alterar iteração para listas
	{
		fprintf(stderr, "arg:%d\n", i);
		process_ctl(av[i++], env, 1); // Loop to redirect and execute subsequent commands.
	}
	execute(av[i], env); // Execute the final command.
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
	cmd_struct.is_built_in = true;
	cmd_struct.red_type = "append";

	simple_cmd(cmd_struct);
}