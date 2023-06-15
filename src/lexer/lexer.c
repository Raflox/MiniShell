/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:04:39 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/12 11:17:26 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_lexer
{
	char	*cmd;
}t_lexer;

void	print_linked_list(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	if (!lst)
		return ;
	while (temp)
	{
		printf("%%%s%%\n", ((t_lexer *)temp->content)->cmd);
		temp = temp->next;
	}
}

t_list	*new_cmd(char *str)
{
	t_lexer	*cmd;

	cmd = malloc(sizeof(t_lexer));
	if (!cmd)
		return (NULL);
	cmd->cmd = str;
	return (ft_lstnew((t_lexer *)cmd));
}

void	lexer(char *str)
{
	t_list	*lst;
	int		i;
	int		start;
	int		end;

	i = -1;
	start = 0;
	end = 0;
	lst = 0;
	while (str[++i])
	{
		if (str[i] == PIPE)
			ft_lstadd_back(&lst, new_cmd(ft_substr(str, i, 1)));
		else
		{
			while (ft_is_space(str[i]))
				i++;
			start = i;
			while (!ft_is_space(str[i]) && str[i] != PIPE && str[i] != '\0')
				i++;
			end = i;
			while (ft_is_space(str[i]) && str[i] != PIPE)
				i++;
			ft_lstadd_back(&lst, new_cmd(ft_substr(str, start, end - start)));
			start = i + 1;
			if (str[i] == PIPE)
				i--;
		}
	}
	print_linked_list(lst);
}
