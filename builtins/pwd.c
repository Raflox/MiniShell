/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:45:01 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/04 11:41:45 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	char	*buffer;
	size_t	size;

	size = 100;
	buffer = (char *)malloc(size);
	if (buffer == NULL)
	{
		perror("malloc");
		return (1);
	}

	if (getcwd(buffer, size) != NULL)
		printf("Current working directory: %s\n", buffer);
	else
		perror("getcwd");

	free(buffer);
	return (0);
}
