/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:34 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/27 12:04:10 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO:	ADD FUNCTION TO CLEAN AND CLOSE UPON ERROR?

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

static char	*find_path(char **envp, char *cmd)
{
	int		index;
	char	*path;
	char	*temp;
	char	**paths;
	int		i;

	path = NULL;
	temp = NULL;
	paths = NULL;
	if (!envp || !envp[0])
		return (ft_strdup(cmd));
	index = find_env_path(envp);
	if (index == -1)
		return (NULL);
	path = &envp[index][6];
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, F_OK) != -1)
		{
			free(temp);
			free_array(&paths);
			return (path);
		}
		free(temp);
		free(path);
		i++;
	}
	free_array(&paths);
	return (ft_strdup(cmd));
}

void	error_before_execute(char *path)
{
	struct stat	st;
	
	if (stat(path, &st) == -1)
		return ;
	if (S_ISDIR(st.st_mode) && path && (!ft_strncmp("./", path, 2) || path[0] == '/'))
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
				display_error(126," No such file or directory", true);
			else
				display_error(127," No such file or directory", true);
		}
		else
			display_error(127," command not found", true);
	}
	free(path);
}
