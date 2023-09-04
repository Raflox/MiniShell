/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:33:11 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/04 23:42:28 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

// TODO: Check arguments for this function.
// TODO: Check arguments for echo().
// TODO: Improve env() acording to struct.
// FIXME: Error handling cd() -> no dir

void built_in(char *input, char **envp)
{
	char **temp;
	if (!ft_strncmp(input, "cd", 2))
	{
		temp = ft_split(input, ' ');
		cd(temp[1]);
		clean_matrix(temp);
	}
	if (!ft_strncmp(input, "echo", 4))
	{
		if (!(ft_strncmp(input, "echo -n", 7)))	
			echo(input, 1);
		else
			echo(input, 0);
	}
	if (!ft_strncmp(input, "env", 3))
		env(envp);
	if (!ft_strncmp(input, "pwd", 3))
		pwd();
/* 	if (!ft_strncmp(input, "export", ft_strlen(input)))
	if (!ft_strncmp(input, "unset", ft_strlen(input)))
	if (!ft_strncmp(input, "exit", ft_strlen(input))) */
}

int main(int ac, char **av, char **env)
{
	while (1)
	{
		char *input = readline("Minishell>> ");
		built_in(input, env);
		free(input);
	}
}
