/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:44:54 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 12:32:29 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_pwd(char ***env)
{
	char	buf[PATH_MAX + 1];
	char	*cmd;

	getcwd(buf, sizeof(buf));
	cmd = ft_strjoin("PWD=", buf);
	update_env(env, cmd);
	if (find_var(*env, "OLDPWD") == -1)
		update_env(env, "OLDPWD");
	free(cmd);
}

void	update_shlvl(char ***env, char *value)
{
	char	*shlvl;
	char	*new;

	if (!value)
		return ;
	shlvl = ft_itoa(ft_atoi(value) + 1);
	new = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	update_env(env, new);
	free(new);
}

char	**get_env(char **envp)
{
	char	**env;
	char	*var;
	int		i;

	if (!envp)
		return (NULL);
	env = copy_array(envp);
	i = -1;
	while (env[++i])
	{
		var = get_env_var(env[i]);
		if (!ft_strcmp("SHLVL", var))
		{
			update_shlvl(&env, &env[i][ft_strlen(var) + 1]);
			get_pwd(&env);
			free(var);
			return (env);
		}
		free(var);
	}
	update_env(&env, "SHLVL=1");
	get_pwd(&env);
	return (env);
}
