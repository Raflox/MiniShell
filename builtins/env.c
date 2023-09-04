/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:38:28 by rafilipe          #+#    #+#             */
/*   Updated: 2023/08/30 22:09:17 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
    int		i;
    char	*scpy;

    i = 0;
    while (s1[i] != '\0')
        i++;
    scpy = malloc(i * sizeof(char) + 1);
    if (!scpy)
        return (0);
    while (i >= 0)
    {
        scpy[i] = s1[i];
        i--;
    }
    return (scpy);
}

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

void	env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char **my_env;

	my_env = matrix_cpy(env);

    int i = 0;

    while (my_env[i])
    {
        printf("%s\n", my_env[i]);
        i++;
    }
}
