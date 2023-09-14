/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:06:42 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/13 18:10:00 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	is_built_in(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1]);
	else if (!ft_strcmp(cmd[0], "echo"))
	{
		if (cmd[1] && !(ft_strcmp(cmd[1], "-n")))	
			echo(cmd[2], 1);
		else if (cmd[1])
			echo(cmd[1], 0);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		env(shell()->env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd[0], "unset"))
		unset(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		export(cmd);
	/* if (!ft_strcmp(input, "exit", ft_strlen(in))) */
}
