/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:39:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 17:26:07 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ------------------------------- INCLUDES --------------------------------- //

# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
// boolean lib
# include <stdbool.h>
//minishell libs
# include "parsing.h"
# include "utils.h"
# include "lexer.h"

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_sh		t_sh;
typedef struct s_var	t_var;

struct s_sh
{
	bool	prompt;
	bool	error;
	t_var	*vars;
	t_list	*segment_lst;
};

struct s_var
{
	char	**env;
	char	**new_vars;
};


// -----------------------------  FUNCTIONS --------------------------------- //

t_sh	*shell(void);

#endif
