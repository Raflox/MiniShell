/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:45:01 by rafilipe          #+#    #+#             */
/*   Updated: 2023/09/14 13:24:59 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(void)
{
	char	buf[PATH_MAX + 1];

	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		perror("getcwd");
}
