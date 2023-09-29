/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 10:18:10 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Principal struct
*/
t_sh	*shell(void)
{
	static t_sh	shell;

	return (&shell);
}

//Just print an array
void	print_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		printf("%s\n", array[i]);
}

// return diff between s1 and s2, greater if s1 is after
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

//just copy an array
char	**copy_array(char **array)
{
	char	**new;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (array[++i])
		new[i] = ft_strdup(array[i]);
	new[i] = NULL;
	return (new);
}

/*
	This function frees the array if it exists
*/
void	free_array(char ***array)
{
	int		i;
	int		len;

	if (!(*array))
		return ;
	len = 0;
	while ((*array)[len])
		len++;
	i = -1;
	while (++i < len)
		free((*array)[i]);
	free((*array));
}
