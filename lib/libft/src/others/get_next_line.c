/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 12:29:53 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/29 09:38:58 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	str_len(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

static char	*ft_join(char *line, char *stash)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc((str_len(line) + str_len(stash)) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (line && line[++i])
		ret[i] = line[i];
	i += (!line);
	free(line);
	while (*stash)
	{
		ret[i++] = *stash;
		if (*stash++ == '\n')
			break ;
	}
	ret[i] = '\0';
	return (ret);
}

static int	ft_nextclean(char *stash)
{
	int	nl_flag;
	int	j;

	j = 0;
	nl_flag = 0;
	while (*stash)
	{
		if (*stash == '\n')
		{
			nl_flag = 1;
			*stash++ = 0;
			break ;
		}
		*stash++ = 0;
	}
	if (nl_flag)
	{
		while (*stash)
		{
			stash[j++] = *stash;
			*stash = 0;
		}
	}
	return (nl_flag);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			i;

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
