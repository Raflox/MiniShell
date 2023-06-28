/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:28:27 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/06/26 22:53:44 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// ------------------------------- INCLUDES --------------------------------- //

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_seg	t_seg;

struct s_seg
{
	char			**cmd;
	char			**red;
};

// -----------------------------  FUNCTIONS --------------------------------- //

void	parse(char *input);

/*

**	parsing utils

*/
//utils0.c
int		is_space(char c);
int		is_token(char c);
int		is_quote(char c);
int		is_greatorless(char c);

//utils1.c -- full
char	*find_and_replace(char *str, char *find_set, char replace_char);
char	**split_and_trim(char *str, char c);
void	add_str_to_array(char ***array, char *str);



#endif