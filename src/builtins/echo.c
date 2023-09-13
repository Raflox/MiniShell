/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:49:41 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/13 17:46:26 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(char *str, int flag)
{
	if (!str)
	{
		printf("\n");
		return ;
	}
	if (!flag)
	{
		printf("%s", str);
		printf("\n");
	}
	else
	{
		printf("%s", str);
	}
}
