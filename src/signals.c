/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:14:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/27 12:12:30 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("^C\n", 0);
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