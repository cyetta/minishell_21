#For MAC
#
#Need to install readline 8.1 -> brew install readline
#uninstall -> brew cleanup readline
#readline is keg-only, which means it was not symlinked into /.brew,
#because macOS provides BSD libedit.
#
#For compilers to find readline you may need to set:
#  export LDFLAGS="-L$HOME/.brew/opt/readline/lib"
#  export CPPFLAGS="-I$HOME/.brew/opt/readline/include"
#
#To install Homebrew on Mac - https://github.com/kube/42homebrew
#
#To install readline in Linux do
#sudo apt update
#sudo apt install libreadline-dev
#sudo apt install libreadline8

NAME	= minishell
BNS_N	=

SRC_N 	= ft_util.c minishell.c builtins1.c builtins2.c ft_error.c ld_env2lst.c \
		lexer.c lexer_dp.c lexer_qsp.c lexer_rdr.c lexer_util.c \
		parser_expstr.c parser_util.c parser.c parser_tkn1.c parser_tkn2.c \
		exec_lst_ld.c

SRC_B 	=


DIR_SRC	= ./
DIR_BON	= ./
DIR_LIBFT = ./ft_lib/
DIR_RDLINE = ${HOME}/.brew/opt/readline
INCPATH	= ${DIR_SRC} ${DIR_LIBFT}

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

ifdef DESKTOP_SESSION
# for Linux
INCRDLN =
LIBRDLN = -lreadline
else
# for Mac
INCRDLN = -I${DIR_RDLINE}/include
LIBRDLN = -L ${DIR_RDLINE}/lib -lreadline -lhistory
endif

SRCS_P	= ${addprefix ${DIR_SRC}, ${SRC_N}}
SRCS_B	= ${addprefix ${DIR_BON}, ${SRC_B}}

OBJ_P	= ${SRCS_P:.c=.o}
OBJ_B	= ${SRCS_B:.c=.o}

DPDS	= ${SRCS_P:.c=.d} ${SRCS_B:.c=.d}

all:	${NAME}

%.o : %.c
	${CC} ${CFLAGS} -MMD -c $< -o $@ -I${DIR_SRC} -I${DIR_LIBFT} ${INCRDLN}

include ${wildcard ${DPDS}}

${DIR_LIBFT}libft.a:
#	${MAKE} CFLAG="${CFLAGS} -g3" -C ${DIR_LIBFT}
	${MAKE} -C ${DIR_LIBFT}

${NAME}: ${DIR_LIBFT}libft.a ${OBJ_P}
	${CC} ${CFLAGS} -o $@ ${OBJ_P} -L ${DIR_LIBFT} -lft ${LIBRDLN}

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
