/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:11:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/13 14:59:29 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(char	**cmd)
{
	char	*temp;
	int		i;
	int		array_index;

	if (!cmd || ft_strcmp(cmd[0], "unset") != 0)
		return ;
	if (cmd[1])
	{
		i = 0;
		while (cmd[++i])
		{
			array_index = -1;
			while (shell()->env[++array_index])
			{
				temp = get_env_var(shell()->env[array_index]);
				if (ft_strcmp(cmd[i], temp) == 0)
				{
					rm_str_from_array(&shell()->env, array_index);
					free(temp);
					break ;
				}
				free(temp);
			}
		}
	}
}
