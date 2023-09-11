/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:45:01 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/11 15:13:02 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*buffer;
	size_t	size;

	size = 100;
	buffer = (char *)malloc(size);
	if (buffer == NULL)
	{
		perror("malloc");
		return (1);
	}

	if (getcwd(buffer, size) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");

	free(buffer);
	return (0);
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
