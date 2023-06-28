/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:11:22 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/26 22:53:31 by rgomes-c         ###   ########.fr       */
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

/*
**	Function: find_and_replace_handling_quotes
**	---------------------------------
**	This function look for character outside of quotes
**	and switch them with a replace character.

**	Parameters:
**		str:				input string.
**		find_char:			character to find.
**		replace_char:		character to replace.

**	Return:
**		string.
*/
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

/*
**	Function: split_and_trim
**	---------------------------------
**	This function split the input by a given character.
**	Then trim each segment with spaces to simplify.
**	This function allocates memory (array).

**	Parameters:
**		input:		input string.

**	Return:
**		char **array
*/
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
		free(*array);
		*array = new_array;
	}
}
