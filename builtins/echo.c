/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:49:41 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/04 15:20:00 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i = 0;

	while(str[i])
		i++;
	return (i);
}

void	echo(char *str, int fd, int flag)
{
	int	len;

	if (!str)
	{
		write(fd, "\n", 1);
		return ;
	}
	len = ft_strlen(str);
	write(fd, str, len);
	if (flag)
		write(fd, "\n", 1);
	//printf("%d\n", len);
}

int	main(int argc, char **argv)
{
	if (argc == 4)
		echo("Hello", 0, 1);
	else if (argc == 3)
		echo("Hello", 0, 0);
/* 	while (1)
	{
		char *input = readline("Minishel>> ");
		if (!(ft_strncmp(input, "echo", 4)))
		{
			echo(input, 0);
		}
		free(input);
	} */
	
}