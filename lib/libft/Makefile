NAME = libft.a

CC = @cc

CFLAGS = -Wall -Wextra -Werror

RM = @rm -f

SRC = src/conv/ft_atoi.c         src/is/ft_isdigit.c        src/lst/ft_lstmap.c        src/mem/ft_memmove.c       src/str/ft_split.c         src/str/ft_strncmp.c \
src/conv/ft_itoa.c         src/is/ft_isprint.c        src/lst/ft_lstnew.c        src/mem/ft_memset.c        src/str/ft_strchr.c        src/str/ft_strnstr.c \
src/conv/ft_strmapi.c      src/lst/ft_lstadd_back.c   src/lst/ft_lstsize.c       src/others/ft_printf.c     src/str/ft_strdup.c        src/str/ft_strrchr.c \
src/conv/ft_tolower.c      src/lst/ft_lstadd_front.c  src/mem/ft_bzero.c         src/others/get_next_line.c src/str/ft_striteri.c      src/str/ft_strtrim.c \
src/conv/ft_toupper.c      src/lst/ft_lstclear.c      src/mem/ft_calloc.c        src/put/ft_putchar_fd.c    src/str/ft_strjoin.c       src/str/ft_substr.c \
src/is/ft_isalnum.c        src/lst/ft_lstdelone.c     src/mem/ft_memchr.c        src/put/ft_putendl_fd.c    src/str/ft_strlcat.c \
src/is/ft_isalpha.c        src/lst/ft_lstiter.c       src/mem/ft_memcmp.c        src/put/ft_putnbr_fd.c     src/str/ft_strlcpy.c \
src/is/ft_isascii.c        src/lst/ft_lstlast.c       src/mem/ft_memcpy.c        src/put/ft_putstr_fd.c     src/str/ft_strlen.c

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
			@ar rcs $(NAME) $(OBJ)
			@echo "\nlib compiled\n"

clean:
			$(RM) $(OBJ)

fclean:	clean
			$(RM) $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re