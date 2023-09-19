/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:40 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 18:11:53 by rafilipe         ###   ########.fr       */
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

	/* int fd;
	char *line; */

	(void)ac;
	(void)av;
	//init_shell();
	signals(0);
	shell()->export = get_export(envp);
	shell()->env = copy_array(envp);
	shell()->pwd = "MINISHELL > ";
	while (1)
	{
		sh_line = readline(shell()->pwd);
		if (!sh_line)
			return (0);
		if (sh_line[0] != '\0')
		{
			add_history(sh_line);
			parse(sh_line);
			//export(((t_seg *)(shell()->segment_lst)->content)->cmd);
			//unset(((t_seg *)(shell()->segment_lst)->content)->cmd);
			//env(((t_seg *)(shell()->segment_lst)->content)->cmd);
			if (((t_seg *)shell()->segment_lst->content)->builtin && !shell()->error)
				is_built_in(((t_seg *)shell()->segment_lst->content)->cmd);
			else
			{
				if (!shell()->error)
					executeCommandList(shell()->segment_lst);
			}
		/* 	if (((t_seg *)shell()->segment_lst->content)->here)
			{
				heredoc(((t_seg *)shell()->segment_lst->content));
				while((line = get_next_line(fd)))
				{
					fprintf(stderr, "%s", line);
					free(line);
				}
			} */
			free_seg();
		}
	}
	(void)sh_line;
	return (0);
}
