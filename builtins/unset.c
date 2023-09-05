/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:09:10 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/05 13:26:24 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*scpy;

	i = 0;
	scpy = malloc(n * sizeof(char) + 1);
	if (!scpy)
		return (0);
	while (i < n)
	{
		scpy[i] = s1[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}

void	unset(char *var)
{
	char	**temp;
	char    **aux;
	int		i;
    int     len;

	i = 0;
    len = 0;
    aux = config()->my_env;
	while (*aux)
    {
        len++;
        aux++;
    }
	temp = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		if (!ft_strncmp(temp[i], var, ft_strlen(var)))
			temp[i] = ft_strndup(config()->my_env[i], (ft_strlen(var) + 1));
		else
			temp[i] = ft_strdup(config()->my_env[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}