/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:36:36 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/11 15:35:31 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
#define BUILT_IN_H

// ------------------------------- INCLUDES --------------------------------- //

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

// -----------------------------  FUNCTIONS --------------------------------- //

void	cd(char *str);
void	echo(char *str, int flag);
int		pwd(void);
void	env(char **cmd);
void	export(char	**cmd);
void	unset(char	**cmd);

//env/utils.c
int		search_var_in_array(char *str, char **array);
void	rm_str_from_array(char ***array, int index);
char	**get_export(char **envp);
char	**sort_alpha_array(char **array);
void	update_env(char	***env, char *cmd);
char	*create_line_export(char *str);

#endif