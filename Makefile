#Colors
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
COLOUR_END	=	\033[0m

#Targets
NAME = minishell

#Compiler flags
CC = @cc
CFLAGS = -Wall -Wextra -Werror -I$(INC) -g #-fsanitize=address,undefined
LDFLAGS= -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include -lreadline
RM = @rm -rf

#libft
LIBFT_DIR	=	lib/libft/
LIBFT_A		=	lib/libft/libft.a

#Source files
SRC			=	src/main.c  src/signals.c  src/builtins/echo.c  src/builtins/unset.c  src/parse/parseSegments.c            src/parse/utils_exit.c  src/parse/utils_str.c    src/utils/utils0.c \
src/builtins/cd.c        src/builtins/pwd.c   src/parse/parse.c     src/parse/parseSegmentsConditions.c  src/parse/utils_is.c    src/utils/debug_utils.c  src/utils/utils1.c 	src/builtins/built_in.c	src/builtins/env/env.c src/builtins/env/get_env.c src/builtins/export.c src/builtins/exit.c\
src/pipex/executor.c	src/pipex/utils.c src/pipex/heredoc.c


#Object files
OBJ			=	$(SRC:src/*/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		=	obj

INC			= include/

all: $(NAME)

$(NAME):	$(OBJ) | $(OBJ_DIR)
	@echo "$(BLACK)Compiling libft...$(COLOUR_END)"
	@make --silent -C $(LIBFT_DIR)
	@echo "$(GREEN)libft successfully compiled.$(COLOUR_END)"
	@echo "$(BLACK)Compiling $(NAME)...$(COLOUR_END)"
	@$(CC) $(CFLAGS) -o $(@) -I/usr/local/include $(^) $(LIBFT_A) -lreadline
	@echo "$(GREEN)$(NAME) successfully compiled.$(COLOUR_END)"

$(OBJ_DIR)/%.o:	src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $(^) -o $(@)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean --silent -C $(LIBFT_DIR)
	@echo "$(YELLOW)All Objects removed.$(COLOUR_END)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean --silent -C $(LIBFT_DIR)
	@echo "$(YELLOW)$(NAME) removed.$(COLOUR_END)"

re: fclean all

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --track-fds=yes ./minishell 2>valgrind.log

.PHONY: all clean fclean re bonus