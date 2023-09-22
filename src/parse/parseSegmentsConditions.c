/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSegmentsConditions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:43:00 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/22 22:10:35 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_quote(char *str, char **new_str, char quote, int *curr_pos);

int	get_variable_size(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	expander(char *old_str, char **new_str, int start, int *curr_pos)
{
	char	*expand_temp;
	char	*temp;
	int		i;
	int		j;

	expand_temp = NULL;
	temp = NULL;
	while (start < *curr_pos)
		add_c_to_string(&expand_temp, old_str[start++]);
	i = -1;
	while (shell()->env[++i])
	{
		j = get_variable_size(shell()->env[i]);
		temp = ft_substr(shell()->env[i], 0, j);
		if (ft_strcmp(expand_temp, temp) == 0)
		{
			free(temp);
			while (shell()->env[i][++j])
				add_c_to_string(new_str, shell()->env[i][j]);
			break ;
		}
		free(temp);
	}
	free(expand_temp);
}

/*
**	Function: expand_variable
**	---------------------------------
**	This function expand the variables if it possible to expand.

**	Parameters:
**		input:		input string.
**		curr_pos:	current position on string.

**	Return:
**		Non.
*/
static void	expand_variable(char *old_str, char **new_str, int *curr_pos)
{
	int		start;
	char	*exit_var;
	int		i;

	(*curr_pos)++;
	if (ft_isdigit(old_str[(*curr_pos)]))
	{
		(*curr_pos)++;
		return ;
	}
	start = *curr_pos;
	while ((ft_isalpha(old_str[(*curr_pos)]) \
		|| ft_isdigit(old_str[(*curr_pos)]) \
		|| old_str[*curr_pos] == '_'))
		(*curr_pos)++;
	if (old_str[(*curr_pos)] == '?')
	{
		(*curr_pos)++;
		exit_var = ft_itoa(shell()->exit_code);
		i = -1;
		while (exit_var[++i])
			add_c_to_string(new_str, exit_var[i]);
		free(exit_var);
	}
	else if (start != *curr_pos)
		expander(old_str, new_str, start, curr_pos);
	else
		add_c_to_string(new_str, '$');
}

/*
**	Function: skip_quote
**	---------------------------------
**	This function skip all the quoted content and
**	give an error when quotes arent closed

**	Parameters:
**		input:		input string.
**		quote:		char ' or " that was is that position.
**		curr_pos:	current position on string.

**	Return:
**		Non.
*/
static int	skip_quote(char *str, char **new_str, char quote, int *curr_pos)
{
	while (str[++(*curr_pos)])
	{
		if (quote == '\"' && str[*curr_pos] == '$')
			expand_variable(str, new_str, curr_pos);
		if (str[*curr_pos] == quote)
		{
			(*curr_pos)++;
			return (1);
		}
		if (str[*curr_pos] == '\0')
			break ;
		add_c_to_string(new_str, str[*curr_pos]);
	}
	return (0);
}

void	parse_segment_conditions(char *str, char **new_str, int *curr_pos)
{
	if (is_quote(str[*curr_pos]))
	{
		if (!skip_quote(str, new_str, str[*curr_pos], curr_pos))
			readline_error("minishel: doens't interpret unclosed quotes", 0, 0);
	}
	else if (str[*curr_pos] == '$')
		expand_variable(str, new_str, curr_pos);
	else
		add_c_to_string(new_str, str[(*curr_pos)++]);
}
