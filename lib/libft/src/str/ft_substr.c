/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:53:13 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sp;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	sp = malloc((len + 1) * sizeof(char));
	if (!sp)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len && start < ft_strlen(s))
	{
		sp[i] = s[start];
		i++;
		start++;
	}
	sp[i] = '\0';
	return (sp);
}
