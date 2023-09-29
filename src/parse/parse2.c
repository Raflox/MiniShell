/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:23:54 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 12:57:27 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "export") == 0 || ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	init_built_in_flag(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		seg->builtin = false;
		i = -1;
		while (seg->cmd && seg->cmd[++i])
		{
			if (is_builtin(seg->cmd[i]))
				seg->builtin = true;
		}
		temp = temp->next;
	}
}

int	pip_between(char *input)
{
	int		i;
	char	quote;
	char	last_c;

	i = 0;
	last_c = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i++] != quote)
				return (0);
			last_c = 0;
		}
		else if (is_space(input[i]))
			i++;
		else if (last_c == '|' && input[i] == '|')
			return (1);
		else
			last_c = input[i++];
	}
	return (0);
}

int	pipe_sintax(char *input)
{
	int	i;

	if (!input || !(*input))
		return (0);
	i = 0;
	while (input[i] && is_space(input[i]))
		i++;
	if (input[i] == '|')
		return (1);
	i = ft_strlen(input) - 1;
	while (input[i] && is_space(input[i]))
		i--;
	if (input[i] == '|')
		return (1);
	if (pip_between(input))
		return (1);
	return (0);
}

// char	*parse_red(char *seg, int *curr_pos)
// {
// 	char	*red;
// 	char	*temp;
// 	char	*final;

// 	red = NULL;
// 	temp = NULL;
// 	final = NULL;
// 	add_c_to_string(&red, seg[(*curr_pos)++]);
// 	if (seg[(*curr_pos) - 1] == seg[(*curr_pos)])
// 		add_c_to_string(&red, seg[(*curr_pos)++]);
// 	while (seg[(*curr_pos)] && is_space(seg[*curr_pos]))
// 		(*curr_pos)++;
// 	if (seg[(*curr_pos)] && !is_greatorless(seg[(*curr_pos)]))
// 	{
// 		temp = parse_word(seg, curr_pos, red);
// 		if (temp)
// 		{
// 			final = ft_strjoin(red, temp);
// 			free(temp);
// 		}
// 	}
// 	else
// 		display_error(1, "Syntax Error", true);
// 	free(red);
// 	return (final);
// }
