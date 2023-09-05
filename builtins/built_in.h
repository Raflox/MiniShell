/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:36:36 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/05 16:33:30 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
#define BUILT_IN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h> // FIXME: DELETE
#include <readline/history.h> //FIXME: DELETE
#include "../lib/libft/include/libft.h"

typedef struct s_cmd
{
	char **my_env;
}	t_cmd;

void	cd(char *str);
void	echo(char *str, int flag);
void	env(char **env);
int		pwd(void);
char	**unset(char *var, char **env);
void	clean_matrix(char **matrix);
char	**matrix_cpy(char **src);


#endif