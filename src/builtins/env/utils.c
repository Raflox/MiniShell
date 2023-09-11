/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:02:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:33:04 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	search_var_in_array(char *str, char **array)
{
	int		is_export;
	int		i;
	int		j;

	is_export = 0;
	if (ft_strncmp(array[0], "declare -x ", 12))
		is_export = 1;
	i = -1;
	while (array && array[++i])
	{
		j = 0;
		while (str && str[j] && str[j] != '=')
			j++;
		if (is_export && ft_strncmp(str, &array[i][11], j) == 0)
			return (i);
		else if (!is_export && ft_strncmp(str, array[i], j) == 0)
			return (i);
	}
	return (-1);
}

void	rm_str_from_array(char ***array, int index)
{
	char	**new_array;
	int		len;
	int		i;

	if (!(*array))
		return ;
	else
	{
		len = 0;
		while ((*array)[len])
			len++;
		new_array = malloc(sizeof(char *) * len);
		if (!new_array)
			return ;
		i = -1;
		len = 0;
		while ((*array)[++i])
		{
			if (i != index)
				new_array[len++] = ft_strdup((*array)[i]);
		}
		new_array[len] = NULL;
		free_array(array);
		*array = new_array;
	}
}

char	**sort_alpha_array(char **array)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (array && array[++i] && array[i + 1])
	{
		j = -1;
		while (array && array[++j] && array[j + 1])
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
	return (array);
}

char	**get_export(char **envp)
{
	char	**new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * i);
	if (!new)
		return (NULL);
	new[i - 1] = NULL;
	i = -1;
	j = 0;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "_=", 2) != 0)
			new[j++] = create_line_export(envp[i]);
	}
	return (sort_alpha_array(new));
}
