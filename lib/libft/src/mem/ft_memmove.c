/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:18:38 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

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
