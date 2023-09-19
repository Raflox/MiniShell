/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:26:52 by rafilipe          #+#    #+#             */
/*   Updated: 2023/01/30 22:48:19 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

char	*ft_join(char *line, char *stash)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc((ft_strlen(line) + ft_strlen(stash)) + 1);
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

int ft_nextclean(char *stash)
{
    int nl_flag = 0;
    int i;
	int j;

	i = 0;
	j = 0;

    while (stash[i])
    {
        if (stash[i] == '\n')
        {
            nl_flag = 1;
			stash[i++] = 0;
            break;
        }
		stash[i++] = 0;
    }
   	if (nl_flag)
	{
		while (stash[i])
		{
			stash[j++] = stash[i];
			stash[i++] = 0;
		}
	}
	return (nl_flag);
}
