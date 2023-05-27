/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:37:17 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*scpy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	scpy = malloc(i * sizeof(char) + 1);
	if (!scpy)
		return (0);
	while (i >= 0)
	{
		scpy[i] = s1[i];
		i--;
	}
	return (scpy);
}
