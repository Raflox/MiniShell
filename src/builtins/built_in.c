/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:06:42 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/14 13:38:18 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	is_built_in(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		env(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd[0], "unset"))
		unset(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		export(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
}
