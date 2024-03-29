/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:57:13 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/26 15:36:21 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_pwd_env_format(void)
{
	char	buf[PATH_MAX + 1];
	char	*cmd;

	getcwd(buf, sizeof(buf));
	cmd = ft_strjoin("PWD=", buf);
	return (cmd);
}

int	find_var(char **env, char *var)
{
	char	*temp;
	int		i;

	i = -1;
	while (env[++i])
	{
		temp = get_env_var(env[i]);
		if (!ft_strcmp(temp, var))
		{
			free(temp);
			return (i);
		}
		free(temp);
	}
	return (-1);
}

void	update_pwd_var(void)
{
	char	***ch_env;
	char	*new_pwd;
	char	*temp;

	ch_env = &shell()->env;
	new_pwd = get_pwd_env_format();
	if (find_var(shell()->env, "PWD") == -1)
	{
		if (find_var(*ch_env, "OLDPWD") != -1)
			update_env(ch_env, "OLDPWD");
	}
	else
	{
		if (find_var(*ch_env, "OLDPWD") != -1)
		{
			temp = ft_strjoin("OLDPWD=",
					&(*ch_env)[find_var(shell()->env, "PWD")][4]);
			update_env(ch_env, temp);
			free(temp);
			update_env(ch_env, new_pwd);
		}
		else
			update_env(ch_env, new_pwd);
	}
	free(new_pwd);
}

int	cd_home(void)
{
	int		i;

	i = find_var(shell()->env, "HOME");
	if (i != -1)
	{
		if (chdir(&shell()->env[i][5]) == -1)
		{
			perror("Error:");
			shell()->exit_code = 1;
			return (-1);
		}
		return (0);
	}
	printf("var Home disabled\n");
	return (-1);
}

void	cd(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		cd_home();
	else if (i > 2)
	{
		write(STDERR_FILENO, " too many arguments\n", 20);
		shell()->exit_code = 1;
		return ;
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			perror("Error:");
			shell()->exit_code = 1;
			return ;
		}
	}
	update_pwd_var();
	shell()->exit_code = 0;
}
