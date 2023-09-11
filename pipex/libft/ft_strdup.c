/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:22:22 by rafilipe          #+#    #+#             */
/*   Updated: 2022/10/17 18:38:16 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*out;

	i = 0;
	len = ft_strlen((char *)str);
	out = (char *)malloc(len * sizeof(char) + 1);
	if (!out)
		return (NULL);
	out[len] = '\0';
	while (str[i] != '\0')
	{
		out[i] = str[i];
		i++;
	}
	return (out);
}
