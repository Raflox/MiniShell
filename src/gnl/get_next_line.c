/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 12:29:53 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/08 11:27:26 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int 		i;
	
	i = 0;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		while (stash[i])
			stash[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (*stash || read(fd, stash, BUFFER_SIZE) > 0)
	{
		line = ft_join(line, stash);
		if (ft_nextclean(stash))
			break ;
	}
	return (line);
}
