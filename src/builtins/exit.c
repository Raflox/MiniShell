/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:42:04 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/18 15:36:41 by rgomes-c         ###   ########.fr       */
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
		if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
			continue ;
		else if (!ft_isdigit(cmd[1][i]))
		{
			write(STDERR_FILENO, " numeric argument required\n", 27);
			code = 2;
			break ;
		}
		else if (cmd[1][i + 1] == '\0' && cmd[2])
		{
			write(STDERR_FILENO, " too many arguments\n", 20);
			code = 1;
		}
		else if (cmd[1][i + 1] == '\0')
			code = ft_atoi(cmd[1]);
	}
	shell()->exit_code = code;
	shell()->prompt = false;
}
