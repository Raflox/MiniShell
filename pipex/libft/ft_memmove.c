/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:25:54 by rafilipe          #+#    #+#             */
/*   Updated: 2022/11/02 14:53:12 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*char_dest;
	unsigned char	*char_src;

	if (!dest && !src)
		return (NULL);
	char_dest = (unsigned char *) dest;
	char_src = (unsigned char *) src;
	if (char_dest < char_src)
		return (ft_memcpy(dest, src, n));
	while (n-- > 0)
		char_dest[n] = char_src[n];
	return (dest);
}
