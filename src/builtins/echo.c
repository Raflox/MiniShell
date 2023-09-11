/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:49:41 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/05 09:33:20 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

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
