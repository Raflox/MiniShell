/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:02:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/14 12:54:56 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// ------------------------------- INCLUDES --------------------------------- //

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

// -----------------------------  FUNCTIONS --------------------------------- //

//utils_0.c
void	free_array(char ***array);
void	print_array(char **array);
int		ft_strcmp(char *s1, char *s2);
char	**copy_array(char **array);

//utils1.c
void	free_seg(void);
void	free_all(void);
void	rm_last_c_from_str(char **str);

#endif