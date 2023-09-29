/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 12:43:56 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_shell(t_sh *sh, char **envp)
{
	sh->error = false;
	sh->segment_lst = NULL;
	sh->env = get_env(envp);
	sh->exit_code = 0;
	sh->in_heredoc = false;
}

void	open_single_builtin_red(int *in, int *out, t_seg *seg)
{
	if (seg->std.in != -1)
	{
		*in = dup(STDIN_FILENO);
		dup2(seg->std.in, STDIN_FILENO);
		close(seg->std.in);
	}
	if (seg->std.out != -1)
	{
		*out = dup(STDOUT_FILENO);
		dup2(seg->std.out, STDOUT_FILENO);
		close(seg->std.out);
	}
}

void	run_single_builtin(t_seg *seg)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (seg->red_error == 1)
	{
		display_error(1, NULL, true);
		return ;
	}
	open_single_builtin_red(&in, &out, seg);
	execute_builtin(seg->cmd, seg->red_error);
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	run(t_list *lst)
{
	t_seg	*seg;

	if (!lst)
		return ;
	seg = (t_seg *)lst->content;
	if (seg->builtin && !lst->next)
		run_single_builtin(seg);
	else
		execute_cmd_lst(lst);
}

int	main(int ac, char **av, char **envp)
{
	char	*sh_line;

	(void)av;
	rl_catch_signals = 0;
	handle_signals();
	if (ac != 1)
		return (0);
	shell()->prompt = true;
	init_shell(shell(), envp);
	while (shell()->prompt)
	{
		sh_line = readline("msh> ");
		if (!sh_line)
			break ;
		add_history(sh_line);
		if ((sh_line[0] != '\n' || sh_line[0] != '\0') && !parse(sh_line))
		{
			if (!shell()->error)
				run(shell()->segment_lst);
			free_all(0, 1, 0, 0);
		}
	}
	free_all(1, 0, 1, 0);
	printf("\n");
	return (shell()->exit_code);
}
