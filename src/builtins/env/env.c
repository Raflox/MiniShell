/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:07:10 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:10:32 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	update_env(char	***env, char *cmd)
{
	int	i;
	int	len;

	len = 0;
	while (cmd && cmd[len] && cmd[len] != '=')
		len++;
	if (cmd[len] != '=')
		return ;
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp(cmd, (*env)[i], len) == 0)
		{
			rm_str_from_array(env, i);
			add_str_to_array(env, cmd);
			return ;
		}
	}
	add_str_to_array(env, cmd);
}

void	env(char **cmd)
{
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		print_array(shell()->env);
}
