/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:39:56 by rafilipe          #+#    #+#             */
/*   Updated: 2022/11/02 12:14:42 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) == (ft_strlen(s1) + ft_strlen(s2)))
		str = (ft_strdup(s1));
	else
		str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[(ft_strlen(s1) + ft_strlen(s2))] = '\0';
	while (s2[++j])
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i + j] = s2[j];
	}
	return (str);
}
