/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:49:41 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/26 15:36:32 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_echo_flags(char **cmd, bool *flag)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (i);
		j = 1;
		if (cmd[i][1] == '\0')
			return (i);
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		*flag = true;
	}
	return (i);
}

void	echo(char **cmd)
{
	bool	flag;
	int		i;

	flag = false;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	i = skip_echo_flags(cmd, &flag) - 1;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	shell()->exit_code = 0;
}
