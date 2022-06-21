#Need to install readline 8.1 -> brew install readline
#uninstall -> brew cleanup readline
#readline is keg-only, which means it was not symlinked into /.brew,
#because macOS provides BSD libedit.
#
#For compilers to find readline you may need to set:
#  export LDFLAGS="-L$HOME/.brew/opt/readline/lib"
#  export CPPFLAGS="-I$HOME/.brew/opt/readline/include"

NAME	= minishell
BNS_N	=

SRC_N 	= minishell.c builtins1.c builtins2.c ft_error.c ld_env2lst.c lexer.c lexer_dp.c \
			lexer_q.c lexer_rdr.c lexer_util.c parser.c

SRC_B 	=


DIR_SRC	= ./
DIR_BON	= ./
DIR_LIBFT = ./ft_lib/
DIR_RDLINE = ${HOME}/.brew/opt/readline
#INCPATH	= ${DIR_SRC} ${DIR_LIBFT} ${DIR_RDLINE}/include

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror


SRCS_P	= ${addprefix ${DIR_SRC}, ${SRC_N}}
SRCS_B	= ${addprefix ${DIR_BON}, ${SRC_B}}

OBJ_P	= ${SRCS_P:.c=.o}
OBJ_B	= ${SRCS_B:.c=.o}

DPDS	= ${SRCS_P:.c=.d} ${SRCS_B:.c=.d}

all:	${NAME}

%.o : %.c
	${CC} ${CFLAGS} -MMD -c $< -o $@ -I${DIR_SRC} -I${DIR_LIBFT} -I${DIR_RDLINE}/include

include ${wildcard ${DPDS}}

${DIR_LIBFT}libft.a:
	${MAKE} -C ${DIR_LIBFT}

${NAME}: ${DIR_LIBFT}libft.a ${OBJ_P}
	${CC} ${CFLAGS} -o $@ ${OBJ_P} -L ${DIR_LIBFT} -lft -L ${DIR_RDLINE}/lib -lreadline

debug: ${DIR_LIBFT}libft.a
#	${MAKE} CFLAGS="${CFLAGS} -g3" libft.a
	${MAKE} CFLAGS="${CFLAGS} -g3" ${NAME}

debug_bonus:
	${MAKE} CFLAGS="${CFLAGS} -g3" libft
	${MAKE} CFLAGS="${CFLAGS} -g3" SRC_N="${SRC_B}" DIR_SRC="${DIR_BON}" ${NAME}

bonus: ${DIR_LIBFT}libft.a
	${MAKE} SRC_N="${SRC_B}" DIR_SRC="${DIR_BON}" ${NAME}

clean:
	${RM} ${OBJ_P} ${OBJ_B} ${DPDS}
	${MAKE} -C ${DIR_LIBFT} clean

fclean:
	${RM} ${OBJ_P} ${OBJ_B} ${DPDS} ${NAME}
	${MAKE} -C ${DIR_LIBFT} fclean

re:	fclean all

.PHONY: all bonus clean fclean re debug debug_bonus ${DIR_LIBFT}libft.a
