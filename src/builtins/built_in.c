/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:06:42 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/12 17:15:11 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void is_built_in(char **cmd)
{
	char **temp;
	if (!ft_strncmp(cmd[0], "cd", 2))
		cd(cmd[1]);
	if (!ft_strncmp(cmd[0], "echo", 4))
	{
		if (!(ft_strncmp(cmd[1], "-n", 2)))	
			echo(cmd, 1);
		else
			echo(cmd, 0);
	}
	if (!ft_strncmp(cmd[0], "env", 3))
		env(shell()->env);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		pwd();
	if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd)))
		unset(cmd);
	if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd)))
		export(cmd);
	/* if (!ft_strncmp(input, "exit", ft_strlen(input))) */
}
