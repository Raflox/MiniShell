/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:21:34 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*sp;
	unsigned char	cp;

	sp = (unsigned char *)s;
	cp = (unsigned char)c;
	i = 0;
	while (sp[i])
	{
		if (sp[i] == cp)
			break ;
		i++;
	}
	if (sp[i] == cp)
		return ((char *)sp + i);
	return (0);
}
