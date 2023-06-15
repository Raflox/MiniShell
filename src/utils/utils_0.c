/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/12 10:40:32 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_space(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	ft_is_token(char c)
{
	if (c == PIPE || c == GREAT || c == LESS)
		return (1);
	return (0);
}
