/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:34 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/25 08:38:52 by parallels        ###   ########.fr       */
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

	path = NULL;
	temp = NULL;
	paths = NULL;
	i = 0;
	if (!envp || !envp[0])
		return (ft_strdup(cmd));
	index = find_env_path(envp);
	if (index == -1)
		return (NULL);
	path = find_env_path(envp);
	paths = ft_split(path, ':');
	free (path);
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

void	execute(char **cmd, char **envp)
{
	char	*path;

	path = find_path(envp, cmd[0]);
	if (execve(path, cmd, envp) == -1)
	{
		if (errno == EISDIR)
			write(STDERR_FILENO, "Is a Directory", ft_strlen("Is a Directory"));
		else
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		shell()->exit_code = 127;
	}
}
