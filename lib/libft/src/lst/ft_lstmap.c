/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:44:31 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*linked_lists;

	newlist = lst;
	linked_lists = NULL;
	while (lst)
	{
		newlist = ft_lstnew(f(lst -> content));
		if (!newlist)
		{
			ft_lstdelone(newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&linked_lists, newlist);
		lst = lst -> next;
	}
	return (linked_lists);
}
