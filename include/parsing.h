/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:28:27 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/09/29 13:11:45 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// ------------------------------- INCLUDES --------------------------------- //

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_std	t_std;
typedef struct s_seg	t_seg;

struct	s_std
{
	int	in;
	int	out;
};

struct s_seg
{
	bool	builtin;
	bool	heredoc;
	int		red_error;
	pid_t	pid;
	char	**cmd;
	char	**red;
	char	**red_flags;
	char	**in;
	char	**out;
	char	**here;
	bool	append;
	int		pipe_fd[2];
	t_std	std;
};

// -----------------------------  FUNCTIONS --------------------------------- //

int		parse(char *input);

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

//exit_utils.c
void	readline_error(char *error, int code, bool need_free);
void	expand_variable(char *old_str, char **new_str, int *curr_pos);

//parse
char	*parse_word(char *seg, int *curr_pos, char *red);

//parse2.c
int		pipe_sintax(char *input);
int		pip_between(char *input);
void	init_built_in_flag(t_list *lst);
int		is_builtin(char *str);
char	*parse_red(char *seg, int *curr_pos);

//parse3.c
void	init_seg(t_seg *seg);
int		end_word(char c, char quote);
void	get_segment_util(char *input_seg, int *i, t_seg *new_seg);
t_list	*get_segment(char *input_seg);

//parse4.c
int		get_heredoc(t_list *lst);
int		get_heredoc_2(t_seg *seg);

#endif