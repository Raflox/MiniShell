/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:04:02 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 12:05:42 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_c_to_string(char **str, char c)
{
	char	*new_str;
	int		i;

	if (!(*str))
	{
		new_str = malloc(2);
		if (!new_str)
			return ;
		new_str[0] = c;
		new_str[1] = '\0';
		*str = new_str;
		return ;
	}
	i = 0;
	while ((*str)[i])
		i++;
	new_str = malloc(i + 2);
	i = -1;
	while ((*str)[++i])
		new_str[i] = (*str)[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
}

static char	**create_array(char *str)
{
	char	**array;
	int		i;

	array = malloc(sizeof(char *) * 2);
	if (!array)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	array[0] = ft_strdup(str);
	if (!array[0])
		return (NULL);
	array[1] = NULL;
	return (array);
}

void	add_str_to_array(char ***array, char *str)
{
	char	**new_array;
	int		len;
	int		i;

	if (!(*array))
		*array = create_array(str);
	else
	{
		len = 0;
		while ((*array)[len])
			len++;
		new_array = malloc(sizeof(char *) * (len + 2));
		if (!new_array)
			return ;
		i = -1;
		while ((*array)[++i])
			new_array[i] = ft_strdup((*array)[i]);
		new_array[i] = ft_strdup(str);
		new_array[i + 1] = NULL;
		free_array(array);
		*array = new_array;
	}
}
