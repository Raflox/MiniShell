/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/24 23:36:53 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_shell(t_sh *sh, char **envp)
{
	sh->error = false;
	sh->segment_lst = NULL;
	sh->env = get_env(envp);
	sh->exit_code = 0;
}

void	run_single_builtin(t_seg *seg)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
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

void	display_custom_error(char *str, int exit_code)
{
	if (str != NULL)
		write(2, str, ft_strlen(str));
	if (exit_code == -1)
		shell()->exit_code = errno;
}

int	mainctl(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		return (0);
	return (1);
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
		executeCommandList(lst);
}

int	main(int ac, char **av, char **envp)
{
	char	*sh_line;

	(void)av;
	if (ac != 1)
		return (0);
	shell()->prompt = true;
	init_shell(shell(), envp);
	signals(0);
	while (shell()->prompt)
	{
		sh_line = readline("msh> ");
		if (!sh_line)
			free_all(1, 0, 1, 1);
		if (sh_line[0] != '\n' || sh_line[0] != '\0')
		{
			add_history(sh_line);
			parse(sh_line);
			if (!shell()->error)
				run(shell()->segment_lst);
			free_all(0, 1, 0, 0);
		}
	}
	free_all(1, 0, 1, 0);
	return (shell()->exit_code);
}
