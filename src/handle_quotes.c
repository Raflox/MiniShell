/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:22:11 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/05/29 15:05:07 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
This function takes a str and creates a new string with no single quotes;
The return value should be treated has the final string;
No variable expansion or command substitution occurs;
Single quote with single quotes (all disapear), but not with double quotes;
Both single and double quotes allow escaping characters,
using a backslash () to treat them literally;


FUNCTION DONE*/
char	*single_quotes(char *str)
{
	char	*new;

	new = ft_substr(str, 1, ft_strlen(str) - 2);
	return (new);
}

/*
This function takes a str and creates a new string with no double quotes;The return value should be treated variables or commands;
Double quote with double quotes (all disapear), but not with single quotes;
Both single and double quotes allow escaping characters,
using a backslash () to treat them literally;

NEED REDIRECTING FOR VARIABLES TREATEMENT*/
char	*double_quotes(char *str)
{
	char	*new;

	new = ft_substr(str, 1, ft_strlen(str) - 2);
	return (new);
}

char	*handle_quotes(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	if (str[i] == 39 && (str[len]) == 39)
		return (single_quotes(str));
	else if (str[i] == 34 && (str[len]) == 34)
		return (double_quotes(str));
	return ("teste");
}
