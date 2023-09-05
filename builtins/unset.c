/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:09:10 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/05 16:36:42 by rafilipe         ###   ########.fr       */
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

char	**unset(char *var, char **env)
{
	char	**temp;
	char    **aux;
	int		i;
    int     len;

	i = 0;
    len = 0;
    aux = env;
	if (!var)
		return NULL;
	while (*aux)
    {
        len++;
        aux++;
    }
	temp = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		if (!ft_strncmp(temp[i], var, ft_strlen(var)))
			temp[i] = ft_strndup(env[i], (ft_strlen(var) + 1));
		else
			temp[i] = ft_strdup(env[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}