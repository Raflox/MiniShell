/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 12:54:37 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_seg(void)
{
	t_list	*temp;
	t_list	*next;
	t_seg	*seg;

	temp = shell()->segment_lst;
	while (temp)
	{
		seg = (t_seg *)temp->content;
		if (seg->cmd)
			free_array(&seg->cmd);
		if (seg->red)
			free_array(&seg->red);
		if (seg->in)
			free(seg->in);
		if (seg->out)
			free_array(&seg->out);
		if (seg->out)
			free_array(&seg->here);
		next = temp->next;
		free(seg);
		free(temp);
		temp = next;
	}
}

void	free_all(void)
{
	if (shell()->env)
		free_array(&shell()->env);
	if (shell()->export)
		free_array(&shell()->export);
	if (shell()->pwd)
		free(shell()->pwd);
	free_seg();
}

void	rm_last_c_from_str(char **str)
{
	char	*new;
	int		len;
	int		i;

	if (!*str)
		return ;
	len = ft_strlen(*str);
	new = malloc(len);
	i = -1;
	while (++i < (len - 1))
		new[i] = (*str)[i];
	new[i] = '\0';
	free(*str);
	*str = new;
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
