/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:31:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_set(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*stp;
	size_t	i;
	size_t	f;
	size_t	c;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_set(s1[i], set))
		i++;
	f = ft_strlen(s1);
	while (i < f && ft_set(s1[f - 1], set))
		f--;
	stp = malloc((f - i + 1) * sizeof(char));
	if (!stp)
		return (0);
	c = 0;
	while (i < f)
	{
		stp[c] = s1[i];
		c++;
		i++;
	}
	stp[c] = '\0';
	return (stp);
}
