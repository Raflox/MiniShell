/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:04:21 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		count;
	int		j;

	split = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (0);
	j = 0;
	i = 0;
	while (s[i] != '\0' && ft_count_words(s, c) != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		count = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (i > count)
			split[j] = ft_substr(s, count, i - count);
		j++;
	}
	split[j] = NULL;
	return (split);
}
