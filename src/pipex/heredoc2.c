/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:59:22 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 10:59:51 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_error(char *str)
{
	printf("\nWarning: heredoc on line 1 delimited by EOF (wanted: \"%s\")\n", str);
	handle_signals();
}

void	sig_here(int a)
{
	(void)a;
	free_all(1, 1, 1, 0);
	close(shell()->here_fd[0]);
	close(shell()->here_fd[1]);
	shell()->error = true;
	exit(EXIT_FAILURE);
}
