LIBNAME	= libft.a

CC		= gcc
RM		= rm -f
CFLAG	= -Wall -Wextra -Werror

SRCN = ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_tolower.c ft_toupper.c ft_isascii.c ft_isprint.c \
		ft_atoi.c ft_strchr.c ft_strrchr.c ft_strlen.c ft_strncmp.c ft_strlcat.c ft_strlcpy.c \
		ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memccpy.c ft_memcmp.c ft_memmove.c ft_strnstr.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		get_next_line.c \
		ft_printf.c ft_printf_char.c ft_printf_dec.c ft_printf_hex.c ft_printf_parseflag.c

OBJ		= ${SRCN:.c=.o}

DPDS	= ${SRCN:.c=.d}

all:	${LIBNAME}

%.o : %.c
	${CC} ${CFLAG} -MMD -c $< -o $@

include ${wildcard ${DPDS}}

${LIBNAME}:	${OBJ}
	ar rcs $@ $?

clean:
	${RM} ${OBJ} ${DPDS}

fclean:	clean
	${RM} ${LIBNAME}

re:	fclean all

.PHONY: all bonus clean fclean re
