/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/26 17:30:29 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_shell(void)
{
	shell()->segment_lst = 0;
	//shell()->vars->env = *envp;
}

void	run_single_builtin(t_seg *seg)
{
	int	fds;

	fds = open_fds(seg);
	if (!fds)
	{
		is_built_in(seg->cmd);
		dup2(seg->dup_fd[0], STDIN_FILENO);
		dup2(seg->dup_fd[1], STDOUT_FILENO);
	}
	close(seg->dup_fd[0]);
	close(seg->dup_fd[1]);
}

int	main(int ac, char **av, char **envp)
{
	char	*sh_line;

	(void)ac;
	(void)av;
	//init_shell();
	rl_catch_signals = 0;
	handle_signals();
	shell()->prompt = true;
	shell()->exit_code = 0;
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
			//print_array(((t_seg *)shell()->segment_lst->content)->cmd);
			if (((t_seg *)shell()->segment_lst->content)->builtin
				&& !shell()->error && !shell()->segment_lst->next)
				run_single_builtin(shell()->segment_lst->content);
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
