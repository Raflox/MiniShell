/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/21 14:54:40 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	is_greatorless(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
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
