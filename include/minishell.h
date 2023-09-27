/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:39:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/26 17:44:38 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ------------------------------- INCLUDES --------------------------------- //

# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include <signal.h>
# include <limits.h>
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
	bool	error;
	bool	prompt;
	t_list	*segment_lst;
	char	**env;
	char	**export;
	char	*oldpwd;
	char	*pwd;
	int		exit_code;
}	t_sh;

// -----------------------------  FUNCTIONS --------------------------------- //

t_sh	*shell(void);

//signals.c
void    handle_signals(void);

#endif
