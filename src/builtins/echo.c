/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:49:41 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/11 15:13:03 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(char *str, int flag)
{
	if (!str)
	{
		printf("\n");
		return ;
	}
	if (!flag)
	{
		printf("%s", &str[5]);
		printf("\n");
	}
	else
	{
		printf("%s", &str[8]);
	}
}
