/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseSegments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:00:07 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/22 22:04:09 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_segment_cmd(char ***array, int *index, char **str)
{
	int		i;
	char	*new_str;

	(void)index;
	(void)array;
	i = 0;
	new_str = NULL;
	if (!(*str))
		return ;
	while ((*str)[i])
		parse_segment_conditions(*str, &new_str, &i);
	if (new_str == NULL)
		new_str = ft_strdup("");
	free(*str);
	*str = new_str;
}

void	parse_segment_red(char **str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	if (!(*str))
		return ;
	if ((*str)[i] == (*str)[i + 1])
		add_c_to_string(&new_str, (*str)[i++]);
	add_c_to_string(&new_str, (*str)[i++]);
	while (is_space((*str)[i]))
		i++;
	if ((*str)[i] == '\0')
		readline_error("sh: Syntax error: newline unexpected", 0, 0);
	else if (is_greatorless((*str)[i]))
		readline_error("sh: Syntax error: redirection unexpected", 0, 1);
	while ((*str)[i])
		parse_segment_conditions(*str, &new_str, &i);
	free(*str);
	*str = new_str;
}

void	parse_segments(t_list *lst)
{
	t_list	*temp;
	t_seg	*seg;
	int		i;

	temp = lst;
	while (temp && !shell()->error)
	{
		seg = (t_seg *)temp->content;
		i = -1;
		while (seg->cmd && seg->cmd[++i] && !shell()->error)
			parse_segment_cmd(&seg->cmd, &i, &seg->cmd[i]);
		i = -1;
		while (seg->red && seg->red[++i] && !shell()->error)
			parse_segment_red(&seg->red[i]);
		temp = temp->next;
	}
}
