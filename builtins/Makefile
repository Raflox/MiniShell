################################################################################
#                                    CONFIGS                                   #
################################################################################

NAME     := built_in
CC       := gcc
FLAGS    := -Wall -Wextra -Werror -fsanitize=address -g
LIBFTA		= ../lib/libft/libft.a

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=		cd.c \
					echo.c \
					env.c \
					pwd.c \
					unset.c \
					built_in.c
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f


all:		${NAME}

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(LIBFTA) $(OBJS) -L../lib/libft/ -lft -lreadline -o $(NAME)
			@echo "$(GREEN)Successfully built --> $(YELLOW)$(NAME)$(DEFAULT)"


clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re