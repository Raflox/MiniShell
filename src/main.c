/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 19:12:40 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(void)
{
	shell()->segment_lst = 0;
	//shell()->vars->env = *envp;
	shell()->vars->new_vars = 0;
	shell()->prompt = true;
}

int	main(int ac, char **av, char **envp)
{
	char	*sh_line;

	(void)ac;
	(void)av;
	(void)envp;
	//init_shell();
	while (1)
	{
		sh_line = readline("minishel: ");
		parse(sh_line);
	}
	(void)sh_line;
	return (0);
}
