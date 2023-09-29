/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:24:56 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 13:11:23 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_seg(t_seg *seg)
{
	seg->heredoc = false;
	seg->red_error = 0;
	seg->cmd = NULL;
	seg->red = NULL;
	seg->in = NULL;
	seg->out = NULL;
	seg->here = NULL;
	seg->append = false;
	seg->std.in = -1;
	seg->std.out = -1;
}

int	end_word(char c, char quote)
{
	if ((is_greatorless(c) || is_space(c)) && !quote)
		return (1);
	return (0);
}

void	get_segment_util(char *input_seg, int *i, t_seg *new_seg)
{
	char	*temp;

	temp = NULL;
	if (is_space(input_seg[*i]))
		(*i)++;
	else if (is_greatorless(input_seg[*i]))
	{
		temp = parse_red(input_seg, i);
		if (temp)
		{
			add_str_to_array(&new_seg->red, temp);
			free(temp);
		}
	}
	else
	{
		temp = parse_word(input_seg, i, NULL);
		if (temp)
		{
			add_str_to_array(&new_seg->cmd, temp);
			free(temp);
		}
	}
}

t_list	*get_segment(char *input_seg)
{
	t_seg	*new_seg;
	int		i;

	i = 0;
	new_seg = malloc(sizeof(t_seg));
	if (!new_seg)
		return (NULL);
	new_seg->builtin = false;
	init_seg(new_seg);
	while (input_seg[i] && !shell()->error)
		get_segment_util(input_seg, &i, new_seg);
	return (ft_lstnew((t_seg *)new_seg));
}
