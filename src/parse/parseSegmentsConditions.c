/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSegmentsConditions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:43:00 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 10:19:18 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	expand_exit_code(char **new_str, int *curr_pos)
{
	char	*exit_var;
	int		i;

	(*curr_pos)++;
	exit_var = ft_itoa(shell()->exit_code);
	i = -1;
	while (exit_var[++i])
		add_c_to_string(new_str, exit_var[i]);
	free(exit_var);
}

int	end_variable(char c)
{
	if (!(ft_isalpha(c) || ft_isdigit(c) || c == '_') || c == '?')
		return (1);
	return (0);
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
void	expand_variable(char *old_str, char **new_str, int *curr_pos)
{
	int		start;

	(*curr_pos)++;
	if (ft_isdigit(old_str[(*curr_pos)]))
		return ;
	start = (*curr_pos);
	while (old_str[(*curr_pos)] && !end_variable(old_str[(*curr_pos)]))
		(*curr_pos)++;
	if (old_str[(*curr_pos)] == '?')
		expand_exit_code(new_str, curr_pos);
	else if (start != *curr_pos)
		expander(old_str, new_str, start, curr_pos);
	else
		add_c_to_string(new_str, '$');
	(*curr_pos)--;
}
