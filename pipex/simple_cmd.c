/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:55:04 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/04 14:27:16 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


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

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	char	*cmd;

	if (ac == 2)
		execute(av[1], env);
	if (ac == 3)
	{
		in_fd = file_ctl(av[1], INFILE);
		fprintf(stderr, "AQUI\n");
	}
	if (ac == 4)
	{
		out_fd = file_ctl(av[3], OUTFILE);
	}
	execute(av[2], env);
}