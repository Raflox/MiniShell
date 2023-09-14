/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:07:10 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 13:34:52 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

//get env var (allocates memory)
char	*get_env_var(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

void	update_env_str(char **str, char *new, char *temp_env, char *temp_cmd)
{
	int		env_var;
	int		cmd_var;
	int		len;
	int		i;

	env_var = ft_strlen(temp_env);
	cmd_var = ft_strlen(temp_cmd);
	if ((*str)[env_var] && !new[cmd_var])
		return ;
	len = ft_strlen(*str);
	while (len--)
		rm_last_c_from_str(str);
	i = -1;
	while (new[++i])
		add_c_to_string(str, new[i]);
}

void	update_env(char	***env, char *cmd)
{
	char	*temp_env;
	char	*temp_cmd;
	int		i;

	temp_cmd = get_env_var(cmd);
	i = -1;
	while ((*env) && (*env)[++i])
	{
		temp_env = get_env_var((*env)[i]);
		if (ft_strcmp(temp_env, temp_cmd) == 0)
		{
			update_env_str(&(*env)[i], cmd, temp_env, temp_cmd);
			free(temp_env);
			free(temp_cmd);
			return ;
		}
		free(temp_env);
	}
	free(temp_cmd);
	add_str_to_array(env, cmd);
}

void	print_env(char	**env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (env && env[++i])
	{
		temp = get_env_var(env[i]);
		j = 0;
		while (temp[j])
			j++;
		if (env[i][j] == '=')
			printf("%s\n", env[i]);
		free(temp);
	}
}

void	env(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		print_env(shell()->env);
}
