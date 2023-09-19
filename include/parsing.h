/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:28:27 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/15 12:00:03 by rafilipe         ###   ########.fr       */
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
	int		idx;
	pid_t	pid;
	bool	builtin;
	char	**cmd;
	char	**red;
	char	*in;
	bool	append;
	char	**here;
	char	**out;
	int		pipe_fd[2];
	int		dup_fd[2];
	int		main_fd[2];
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
void	add_c_to_string(char **str, char c);

//debug_utils.c
void	print_lst(t_list *lst);

//parse_segments.c
void	parse_segments(t_list *lst);

//parse_segments_conditions.c
void	parse_segment_conditions(char *str, char **new_str, int *curr_pos);

//exit_utils.c
void	readline_error(char *error, int code, bool need_free);


#endif