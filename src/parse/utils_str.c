/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:11:22 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 12:05:36 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_in_find_set(char c, char *find_set)
{
	int	i;

	i = -1;
	while (find_set && find_set[++i])
		if (find_set[i] == c)
			return (1);
	return (0);
}

char	*find_and_replace(char *str, char *find_set, char replace_char)
{
	int		i;
	int		in_quote;
	char	quote;

	i = -1;
	in_quote = 0;
	quote = 0;
	while (str[++i])
	{
		if (is_quote(str[i]) && !in_quote)
		{
			quote = str[i];
			in_quote = !in_quote;
		}
		else if (in_quote && str[i] == quote)
			in_quote = !in_quote;
		else if (!in_quote && is_in_find_set(str[i], find_set))
			str[i] = replace_char;
	}
	return (str);
}

char	**split_and_trim(char *str, char c)
{
	char	**array;
	char	*temp;
	int		i;

	array = ft_split(str, c);
	if (!array)
		return (NULL);
	i = -1;
	while (array[++i])
	{
		temp = ft_strtrim(array[i], " \t");
		free(array[i]);
		array[i] = temp;
	}
	return (array);
}
