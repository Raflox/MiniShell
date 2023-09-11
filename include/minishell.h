/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:39:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:33:53 by rgomes-c         ###   ########.fr       */
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

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_sh		t_sh;

struct s_sh
{
	bool	error;
	t_list	*segment_lst;
	char	**env;
	char	**export;
	char	*oldpwd;
	char	*pwd;
	int		exit_code;
};

// -----------------------------  FUNCTIONS --------------------------------- //

t_sh	*shell(void);

//signals.c
void	signals(int number);

#endif
