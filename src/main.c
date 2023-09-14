/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 13:42:32 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	shell()->prompt = true;
	shell()->env = get_env(envp);
	while (shell()->prompt)
	{
		sh_line = readline("msh> ");
		if (!sh_line)
			return (0);
		if (sh_line[0] != '\0')
		{
			add_history(sh_line);
			parse(sh_line);
			if (((t_seg *)shell()->segment_lst->content)->builtin
				&& !shell()->error)
				is_built_in(((t_seg *)shell()->segment_lst->content)->cmd);
			else
			{
				if (!shell()->error)
					executeCommandList(shell()->segment_lst);
			}
			free_seg();
		}
	}
	(void)sh_line;
	return (shell()->exit_code);
}
