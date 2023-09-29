/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:42:04 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 09:58:48 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_exit(char **cmd, int i, int *code)
{
	if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
		return (0);
	else if (!ft_isdigit(cmd[1][i]))
	{
		write(STDERR_FILENO, " numeric argument required\n", 27);
		*code = 2;
		return (1);
	}
	else if (cmd[1][i + 1] == '\0' && cmd[2])
	{
		write(STDERR_FILENO, " too many arguments\n", 20);
		*code = 1;
		return (2);
	}
	else if (cmd[1][i + 1] == '\0')
		*code = ft_atoi(cmd[1]);
	return (0);
}

void	ft_exit(char **cmd)
{
	int	i;
	int	code;
	int	x;

	code = 0;
	if (!cmd || ft_strcmp(cmd[0], "exit"))
		return ;
	printf("exit\n");
	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		x = handle_exit(cmd, i, &code);
		if (x == 1)
			break ;
		else if (x == 2)
		{
			shell()->exit_code = code;
			return ;
		}
	}
	shell()->exit_code = code;
	shell()->prompt = false;
}
