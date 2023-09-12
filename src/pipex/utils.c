/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:34 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/11 16:34:18 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// TODO:	ADD FUNCTION TO CLEAN AND CLOSE UPON ERROR?

void	error(char *loc)
{
	fprintf(stderr, "%s\n", loc);
	perror("Error");
	exit(EXIT_FAILURE);
}

static char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;
	char	**paths;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, F_OK) != -1)
			return (path);
		free(temp);
		free(path);
		i++;
	}
	free_array(&paths);
	return (cmd);
}

void	execute(char *cmd, char **envp)
{
	char	**exec_cmd;
	char	*path;

	exec_cmd = ft_split(cmd, ' ');
	cmd = *exec_cmd;
	path = find_path(envp, cmd);
	if (!path)
	{
		free_array(&exec_cmd);
		error("clean path matrix");
	}
	if (execve(path, exec_cmd, envp) == -1)
	{
		fprintf(stderr, "PATH: %s\nexec_cmd: %s\n", path, *exec_cmd);
		error("execve error");
	}
}