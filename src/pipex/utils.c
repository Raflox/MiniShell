/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:34 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 11:44:23 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	find_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

char	*test(char *str, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(str, "/");
	path = ft_strjoin(temp, cmd);
	if (access(path, F_OK) != -1)
	{
		free(temp);
		return (path);
	}
	free(temp);
	free(path);
	return (NULL);
}

static char	*find_path(char **envp, char *cmd)
{
	int		index;
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	paths = NULL;
	if (!envp || !envp[0])
		return (ft_strdup(cmd));
	index = find_env_path(envp);
	if (index == -1)
		return (cmd);
	paths = ft_split(&envp[index][6], ':');
	i = -1;
	while (paths[++i])
	{
		path = test(paths[i], cmd);
		if (path)
		{
			free_array(&paths);
			return (path);
		}
	}
	free_array(&paths);
	return (ft_strdup(cmd));
}

void	error_before_execute(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return ;
	if (S_ISDIR(st.st_mode) && path \
		&& (!ft_strncmp("./", path, 2) || path[0] == '/'))
	{
		display_error(126, " Is a directory", true);
		free_all(1, 1, 1, 1);
	}
}

void	execute(char **cmd, char **envp)
{
	char	*path;

	path = find_path(envp, cmd[0]);
	error_before_execute(path);
	if (execve(path, cmd, envp) == -1)
	{
		if (errno == 14)
		{
			display_error(127, " command not found", true);
		}
		else if (errno == 13)
		{
			if (access(cmd[0], X_OK) && !ft_strncmp("./", cmd[0], 2))
				display_error(126, " No such file or directory", true);
			else
				display_error(127, " No such file or directory", true);
		}
		else
			display_error(127, " command not found", true);
	}
	free(path);
}
