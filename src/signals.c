/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:14:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 10:08:47 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		shell()->exit_code = 130;
		if (shell()->in_exec == true || shell()->in_heredoc)
		{
			printf("\n");
			return ;
		}
		ft_putstr_fd("^C\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		if (shell()->in_exec == true)
		{
			shell()->exit_code = 131;
			ft_putstr_fd("Quit: 3\n", 2);
		}
	}
}

void    handle_signals(void)
{
    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handler);
}