/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:18:38 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/24 15:31:35 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstp;
	unsigned char	*srcp;
	size_t			i;

	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if (!dstp && !srcp)
		return (NULL);
	if (dstp > srcp)
		ft_memcpy(dstp, srcp, len);
	else
	{
		i = -1;
		while (++i < len)
			dstp[i] = srcp[i];
	}
	return (dstp);
}
