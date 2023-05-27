/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:50:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/05/06 23:56:01 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	end_of_line(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	join_stash(char **stash, char *buf, int read_size)
{
	int		len;
	char	*new_stash;
	int		i;
	int		j;

	len = 0;
	while ((*stash)[len])
		len++;
	len += read_size;
	new_stash = malloc(len + 1);
	new_stash[len] = '\0';
	i = -1;
	j = -1;
	while ((*stash)[++j])
		new_stash[++i] = (*stash)[j];
	j = -1;
	while (buf[++j])
		new_stash[++i] = buf[j];
	free(*stash);
	*stash = new_stash;
}

static char	*new_str(char *str, int len)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i])
		i++;
	if (len != 0)
		i = len;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	new[i] = '\0';
	while (--i >= 0)
		new[i] = str[i];
	return (new);
}

static char	*get_line(char **stash, int read_size)
{
	int		i;
	char	*line;
	char	*new;

	i = 0;
	new = 0;
	if (read_size <= 0 && !(*stash))
		return (NULL);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	{
		line = new_str(*stash, i + 1);
		new = new_str(&((*stash)[i + 1]), 0);
	}
	else if ((*stash)[0] != '\0')
		line = new_str(*stash, 0);
	else
		line = NULL;
	free(*stash);
	*stash = new;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buf[BUFFER_SIZE + 1];
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_size = 1;
	while (read_size > 0 && !end_of_line(stash))
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		buf[read_size] = '\0';
		if (!stash)
			stash = new_str(buf, 0);
		else
			join_stash(&stash, buf, read_size);
	}
	return (get_line(&stash, read_size));
}
