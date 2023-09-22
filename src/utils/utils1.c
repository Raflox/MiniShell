/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/22 22:03:11 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_lst(t_list *temp)
{
	t_list	*next;
	t_seg	*seg;

	while (temp)
	{
		next = temp->next;
		seg = (t_seg *)temp->content;
		if (seg && seg->cmd)
			free_array(&seg->cmd);
		if (seg && seg->red)
			free_array(&seg->red);
		if (seg && seg->in)
			free_array(&seg->in);
		if (seg && seg->out)
			free_array(&seg->out);
		if (seg && seg->here)
			free_array(&seg->here);
		if (seg && seg->std.in != -1)
			close(seg->std.in);
		if (seg && seg->std.out != -1)
			close(seg->std.out);
		free(seg);
		free(temp);
		temp = next;
	}
}

void	free_all(bool free_env, bool free_cmd_lst, bool close_std_files, bool f_exit)
{
	if (free_env == true)
		free_array(&shell()->env);
	if (free_cmd_lst == true)
		free_lst(shell()->segment_lst);
	if (close_std_files == true)
	{
		close(2);
		close(1);
		close(0);
	}
	if (f_exit == true)
		exit(shell()->exit_code);
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
