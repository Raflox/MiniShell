/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:42:04 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 10:13:00 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(char **cmd)
{
	int	i;
	int	code;

	code = 0;
	if (!cmd || ft_strcmp(cmd[0], "exit"))
		return ;
	printf("exit\n");
	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			printf("exit: %s: numeric argument required\n", cmd[1]);
			code = 2;
			break ;
		}
		else if (cmd[1][i + 1] == '\0' && cmd[2])
		{
			printf("exit: too many arguments\n");
			code = 1;
		}
		else if (cmd[1][i + 1] == '\0')
			code = ft_atoi(cmd[1]);
	}
	shell()->exit_code = code;
	shell()->prompt = false;
}
