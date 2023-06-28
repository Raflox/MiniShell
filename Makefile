#Colors
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
COLOUR_END	=	\033[0m

#Targets
NAME = minishell

#Compiler flags
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

RM = @rm -rf

#libft
LIBFT_DIR	=	lib/libft/
LIBFT_A		=	lib/libft/libft.a

#Source files
SRC			=	src/main.c \
				src/parse/parse.c                    src/parse/utils_exit.c  src/utils/debug_utils.c \
				src/parse/parseSegments.c            src/parse/utils_is.c    src/utils/utils0.c \
				src/parse/parseSegmentsConditions.c  src/parse/utils_str.c

#Object files
OBJ			=	$(SRC:src/*/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		=	obj

all: $(NAME)

$(NAME):	$(OBJ) | $(OBJ_DIR)
	@echo "$(BLACK)Compiling libft...$(COLOUR_END)"
	@make --silent -C $(LIBFT_DIR)
	@echo "$(GREEN)libft successfully compiled.$(COLOUR_END)"
	@echo "$(BLACK)Compiling $(NAME)...$(COLOUR_END)"
	@$(CC) $(CFLAGS) -o $(@) -lreadline $(^) $(LIBFT_A)
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

.PHONY: all clean fclean re bonus