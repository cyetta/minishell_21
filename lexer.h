/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:02:10 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 23:02:27 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "ft_lib/libft.h"

typedef enum e_lexeme
{
	SPACESTR = 0,
	QUOTES = 1,
	DQUOTES = 2,
	DOLLAR = 3,
	PIPE = 4,
	REDIR_IN = 5,
	REDIR_OUT = 6,
	DREDIR_OUT = 7,
	HERE_DOC = 8,
	STRINGLN = 9
}	t_lexeme;

typedef struct s_token
{
	t_lexeme	e_lxm;
	char		*value;
}	t_token;

int		lexer(t_list **tkn_lst, char *str);
int		new_tkn_elmnt(t_list **new_tkn, t_lexeme lxm, char *value);
void	tkn_elmnt_del(void *elm);
int		is_reserved(char ch);
void	tkn_elmnt_prn(void *elm);
char	*get_subs(char *str, int *pos);
int		add_tkn_sp(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_quotes(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_dquotes(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_dollar(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_pipe(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_rdrin(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_rdrout(t_list **tkn_lst, char *str, int *pos);
int		add_tkn_str(t_list **tkn_lst, char *str, int *pos);

#endif
