/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:22:34 by rafilipe          #+#    #+#             */
/*   Updated: 2023/08/15 17:52:07 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO:	ADD FUNCTION TO CLEAN AND CLOSE UPON ERROR?

void	error(char *loc)
{
	fprintf(stderr, "%s\n", loc);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
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
	clean_matrix(paths);
	return (cmd);
}

void	execute(char *cmd, char **envp)
{
	char	**exec_cmd;
	char	*path;
	int		k;

	exec_cmd = ft_split(cmd, ' ');
	cmd = *exec_cmd;
	path = find_path(envp, cmd);
	if (!path)
	{
		clean_matrix(exec_cmd);
		error("clean path matrix");
	}
	if (execve(path, exec_cmd, envp) == -1)
	{
		fprintf(stderr, "PATH: %s\nexec_cmd: %s\n", path, *exec_cmd);
		error("execve error");
	}
}