/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:34:25 by rafilipe          #+#    #+#             */
/*   Updated: 2022/11/02 14:53:05 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*char_dest;
	unsigned char	*char_src;
	int				i;

	if (!dest && !src)
		return (NULL);
	char_dest = (unsigned char *) dest;
	char_src = (unsigned char *) src;
	i = 0;
	while (n--)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}
