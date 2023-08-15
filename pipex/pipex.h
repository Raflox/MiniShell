/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:24:11 by rafilipe          #+#    #+#             */
/*   Updated: 2023/08/15 23:16:43 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define INFILE 0
# define OUTFILE 1

typedef struct s_pipex {
	int		fd[2];
	pid_t	pid;
	int		pipe_fd[2];
}	t_pipex;

/* UTILS */
void	error(char *loc);
void	execute(char *cmd, char **env);

#endif