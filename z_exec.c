typedef struct s_tkn
{
    int             type;
    s_prim          *command;//f.e.: "ls" or "|" or "some text"
    struct s_token  *prev;
    struct s_token  *next;
}   t_tkn;

typedef struct s_env
{
    char            *key;
    char            *val;
    struct s_env    next;
}   t_env;




typedef stuct s_command
{
	char	*command; // export
	char	**argv;
/*
bbb=
qweqwe
qerwer
wewerwe
/adasd/tmp sdfsf\0 <- "$tmp sdfsf"
wefsdf sfggff\0 <-'wefsdf sfggff'
NULL */
	char	**arge;
	char	*stdin;
	char	*stdout;
	int		pipe
}	t_command;


typedef struct s_prim
{
	t_list	*env; // список переменных окружения
    int     minishell_is_running;// здесь тоже 0 или 1
    int     shlvl;//здесь будут лежать уровни оболочки
    int     process_lvl;//тут будет 3 уровня: дефолтный, родительский, дочерний
    pid_t   pid;//по дефолту тут лежит ноль, но при надобности я буду сюда класть пиды других процессов
    int     std_in;// тут я получу с помощью dup(0) дескриптор
    int     std_out;//тут тоже самое только dup(1)
    int     fd_in;//здесь буду хранить дескрипторы файлов на вход
    int     fd_out;//здесь буду хранить дескрипторы файлов на выход
    int     exit_status;//тут будут лежать коды ошибок
    int     done;//здесь - 0 или 1
}   t_prim;
