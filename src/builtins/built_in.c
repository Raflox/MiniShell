/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:06:42 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/22 18:38:51 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_builtin(char **cmd, int seg_error)
{
	if (seg_error != 0)
	{
		shell()->exit_code = seg_error;
		return ;
	}
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
