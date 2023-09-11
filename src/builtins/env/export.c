/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:40:47 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/11 15:32:57 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*create_line_export(char *str)
{
	char	*new;
	char	*temp1;
	int		i;

	new = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	temp1 = ft_substr(str, 0, i);
	new = ft_strjoin("declare -x ", temp1);
	free(temp1);
	if (str[i - 1] == '=')
	{
		add_c_to_string(&new, '\"');
		while (str[i])
			add_c_to_string(&new, str[i++]);
		add_c_to_string(&new, '\"');
	}
	return (new);
}

void	update_export(char ***export, char *cmd)
{
	char	*temp;
	int		index;
	int		i;

	index = search_var_in_array(cmd, *export);
	if (index != -1)
	{
		i = 0;
		while (cmd && cmd[i] && cmd[i] != '=')
			i++;
		if (cmd[i] != '=')
			return ;
		rm_str_from_array(export, index);
	}
	temp = create_line_export(cmd);
	add_str_to_array(export, temp);
	free(temp);
	*export = sort_alpha_array(*export);
}

int	check_export_conditions(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i] || str[i] == '_')))
			return (0);
	}
	return (1);
}

void	export(char	**cmd)
{
	int	i;

	i = 0;
	if (!cmd || ft_strncmp(cmd[0], "export", 6) != 0)
		return ;
	if (!cmd[1])
		print_array(shell()->export);
	else
	{
		while (cmd[++i])
		{
			if (!check_export_conditions(cmd[i]))
				printf("export: `%s': not a valid identifier\n", cmd[i]);
			else
			{
				update_export(&shell()->export, cmd[i]);
				update_env(&shell()->env, cmd[i]);
			}
		}
	}
}
