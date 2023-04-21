/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:03:22 by rgomes-c          #+#    #+#             */
/*   Updated: 2022/10/21 14:29:46 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list_p;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		list_p = (*lst)-> next;
		ft_lstdelone((*lst), del);
		(*lst) = list_p;
	}
	*lst = NULL;
}
