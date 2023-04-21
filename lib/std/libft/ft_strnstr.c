/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:52:23 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/25 15:26:46 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		n;
	int		nlen;

	if (len == 0 && !haystack)
		return (NULL);
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		n = 0;
		while (haystack[i + n] == needle[n] && (i + n) < len)
		{
			if (nlen - 1 == n)
				return (&((char *)haystack)[i]);
			n++;
		}
		i++;
	}
	return (NULL);
}
