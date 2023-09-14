/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:36:36 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/14 13:24:48 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
#define BUILT_IN_H

// ------------------------------- INCLUDES --------------------------------- //

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

// -----------------------------  FUNCTIONS --------------------------------- //

void	cd(char **cmd);
void	echo(char **cmd);
void	pwd(void);
void	env(char **cmd);
void	export(char	**cmd);
void	unset(char	**cmd);
void	ft_exit(char **cmd);
void	is_built_in(char **cmd);

//env/utils
void	rm_str_from_array(char ***array, int index);
void	update_env(char	***env, char *cmd);
char	*get_env_var(char *str);
char	**get_env(char **envp);
int		find_var(char **env, char *var);

#endif