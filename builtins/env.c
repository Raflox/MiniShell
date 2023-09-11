/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:38:28 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/05 09:40:24 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

char	**matrix_cpy(char **src)
{
	char	**temp;
	int		i;
	char    **aux;
    int     len;

	i = 0;
    len = 0;
    aux = src;
	while (*aux)
    {
        len++;
        aux++;
    }
	temp = (char **)malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		temp[i] = ft_strdup(src[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

// FIXME: Check how bash behaves if env == NULL.
void	env(char **env)
{
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
        printf("%s\n", env[i]);
		i++;
	}
}

/* void	env(char **env)
{
	char **my_env;

	my_env = matrix_cpy(env);

    int i = 0;

    while (my_env[i])
    {
        printf("%s\n", my_env[i]);
        i++;
    }
	clean_matrix(my_env);
} */
