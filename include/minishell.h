/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:39:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 09:34:11 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ------------------------------- INCLUDES --------------------------------- //

# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

//minishell libs
# include "built_in.h"
# include "parsing.h"
# include "utils.h"
# include "pipex.h"

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_sh
{
	bool	prompt;
	bool	error;
	t_list	*segment_lst;
	char	**env;
	int		exit_code;
	bool	in_heredoc;
	int		here_fd[2];
	bool	in_exec;
}	t_sh;

// -----------------------------  FUNCTIONS --------------------------------- //

t_sh	*shell(void);

//signals.c
void	handle_signals(void);
void	display_error(int e_code, char *str, bool error);

#endif
