/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:14:29 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/11/02 09:00:47 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sp;

	sp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (sp[i] == (unsigned char)c)
			return (sp + i);
		i++;
	}
	return (NULL);
}
