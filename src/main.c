/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:18:56 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(void)
{
	shell()->segment_lst = 0;
	//shell()->vars->env = *envp;
}

int	main(int ac, char **av, char **envp)
{
	char	*sh_line;

	(void)ac;
	(void)av;
	//init_shell();
	signals(0);
	shell()->export = get_export(envp);
	shell()->env = copy_array(envp);
	shell()->pwd = "> ";
	while (1)
	{
		sh_line = readline(shell()->pwd);
		if (!sh_line)
			return (0);
		add_history(sh_line);
		parse(sh_line);
		export(((t_seg *)(shell()->segment_lst)->content)->cmd);
		unset(((t_seg *)(shell()->segment_lst)->content)->cmd);
		env(((t_seg *)(shell()->segment_lst)->content)->cmd);
		free_seg();
	}
	(void)sh_line;
	return (0);
}
