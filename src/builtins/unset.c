/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:11:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:12:57 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unset_var_in_export(char *var, char **export)
{
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = -1;
	while (export && export[++i])
	{
		j = 11;
		while (export[i] && export[i][j] && export[i][j] != '=')
			j++;
		temp = ft_substr(export[i], 11, j - 11);
		if (ft_strcmp(var, temp) == 0)
		{
			free(temp);
			return (i);
		}
		free(temp);
	}
	return (-1);
}

int	check_unset_var_in_env(char *var, char **env)
{
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = -1;
	while (env && env[++i])
	{
		j = 0;
		while (env[i] && env[i][j] && env[i][j] != '=')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (ft_strcmp(var, temp) == 0)
		{
			free(temp);
			return (i);
		}
		free(temp);
	}
	return (-1);
}

void	unset(char	**cmd)
{
	int		i;
	int		index;

	if (!cmd || ft_strncmp(cmd[0], "unset", 5) != 0)
		return ;
	if (cmd[1])
	{
		i = 0;
		while (cmd[++i])
		{
			index = check_unset_var_in_export(cmd[i], shell()->export);
			if (index != -1)
				rm_str_from_array(&shell()->export, index);
			index = check_unset_var_in_env(cmd[i], shell()->env);
			if (index != -1)
				rm_str_from_array(&shell()->env, index);
		}
	}
}
