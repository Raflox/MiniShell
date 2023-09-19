/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:24:11 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/14 17:17:49 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include <minishell.h>
# include "../lib/libft/include/libft.h"

# define INFILE 0
# define OUTFILE 1
# define APPEND 2


/* UTILS */
void	error(char *loc);
void	execute(char **cmd, char **env);

/* MAIN */
void	executor(t_seg *seg);
int		heredoc(t_seg *cmd);

//void executeCommand(t_seg *seg);
void executeCommandList(t_list *seg_list);



#endif