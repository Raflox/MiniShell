/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:16 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/05 19:02:31 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: ADD APPEND PERMISSION FOR >>
// TODO: Adapt to work without first infile
// TODO: Close files!!!

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
	return (open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

int main(int ac, char **av, char **env)
{
	int	fd[2]; // 0 = in, 1 = out
	int	i;

	i = 3;
	if (ac == 2)
		execute(av[1], env);
	if (ac >= 4)
	{
		fd[0] = file_ctl(av[1], INFILE); // Open input file.
		fd[1] = file_ctl(av[ac - 1], OUTFILE); // Open output file.		
		dup2(fd[0], STDIN_FILENO); // Redirect standard input to the input file.
		dup2(fd[1], STDOUT_FILENO); // Redirect standard output to the output file.
		process_ctl(av[2], env, fd[0]); // Redirect and execute the first command.
		while (i < ac - 2)
		{
			fprintf(stderr, "arg:%d\n", i);
			process_ctl(av[i++], env, 1); // Loop to redirect and execute subsequent commands.
		}
		execute(av[i], env); // Execute the final command.
	}
	else
		write(STDERR_FILENO, "Invalid number of arguments.\n", 29);

	return (1);
}
