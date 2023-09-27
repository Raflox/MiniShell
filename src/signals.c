/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:14:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/26 17:40:12 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("^C\n", 2);
        	rl_on_new_line();
        	rl_replace_line("", 0);
        	rl_redisplay();
		}
		else
			printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		if (pid != -1)
		{
			ft_putstr_fd("Quit: 3\n", 2);
		}
	}
}

void    handle_signals(void)
{
    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handler);
}
