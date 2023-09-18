/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:14:24 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/18 23:51:07 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int n)
{
	(void) n;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int n)
{
	(void) n;
	rl_redisplay();
	//rl_on_new_line();
}

// void	sigeof_handler(int n)
// {
	
// }

void	signals(int number)
{
	if (number == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		//signal(-1, sigeof_handler);
	}
}