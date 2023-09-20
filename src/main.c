/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/20 16:37:17 by rgomes-c         ###   ########.fr       */
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
	int	in;
	int	out;

	in = -1;
	out = -1;
	open_fds_2(seg);
	if (seg->std.in != -1)
	{
		in = dup(STDIN_FILENO);
		dup2(seg->std.in, STDIN_FILENO);
		close(seg->std.in);
	}
	if (seg->std.out != -1)
	{
		out = dup(STDOUT_FILENO);
		dup2(seg->std.out, STDOUT_FILENO);
		close(seg->std.out);
	}
	is_built_in(seg->cmd);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

int	main(int ac, char **av, char **envp)
{
	char	*sh_line;

	(void)ac;
	(void)av;
	//init_shell();
	signals(0);
	shell()->prompt = true;
	shell()->exit_code = 0;
	shell()->env = get_env(envp);
	while (shell()->prompt)
	{
		sh_line = readline("msh> ");
		if (!sh_line)
		{
			free_all();
			return (0);
		}
		if (sh_line[0] != '\n')
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
	return (shell()->exit_code);
}
