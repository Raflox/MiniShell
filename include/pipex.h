/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:24:11 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 11:00:38 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
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

//void executeCommand(t_seg *seg);
void	execute_cmd_lst(t_list *seg_list);

void	open_reds(t_seg *cmd);
int		heredoc(t_seg *cmd);
void	heredoc_error(char *str);
void	sig_here(int a);

#endif