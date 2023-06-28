/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/28 16:56:12 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Principal struct
*/
t_sh	*shell(void)
{
	static t_sh	shell;

	return (&shell);
}

/*
	This function frees the array if it exists
*/
void	free_array(char ***array)
{
	int		len;
	int		i;

	if (!(*array))
		return ;
	len = 0;
	while ((*array)[len])
		len++;
	i = -1;
	while (++i < len)
		free((*array)[i]);
	free(*array);
}
