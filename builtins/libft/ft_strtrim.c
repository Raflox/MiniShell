/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:42:31 by rafilipe          #+#    #+#             */
/*   Updated: 2022/11/02 12:07:28 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, char c)
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
	char	*str;
	int		len;
	int		i;
	int		n;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_isset(set, s1[i]) && s1)
		i++;
	while (ft_isset(set, s1[len - 1]) && i < len)
		len--;
	str = (char *)malloc(((len - i) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	n = 0;
	while (i < len && s1[i])
		str[n++] = s1[i++];
	str[n] = '\0';
	return (str);
}
