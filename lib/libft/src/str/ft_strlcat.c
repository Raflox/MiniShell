/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:02:30 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		j;
	size_t		slen;
	size_t		dlen;

	slen = ft_strlen(src);
	dlen = 0;
	if (dstsize == 0 && !dst)
		return (0);
	while (dst[dlen] && dlen < dstsize)
		dlen++;
	j = 0;
	while (src[j] && (j + dlen + 1) < dstsize)
	{
		dst[dlen + j] = src[j];
		j++;
	}
	if (dlen < dstsize)
		dst[dlen + j] = '\0';
	return (dlen + slen);
}
