/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:54:56 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/31 02:40:54 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "utils.h"
# include <dirent.h>

enum e_mode
{
	NONE,
	PIPE,
	AND,
	OR
};

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			*here_doc;
	int				mode;
	char			**cmd;
	int				prev_cmd;
}				t_cmd;

typedef struct s_error
{
	char	quote;
	int		par;
	bool	is_start_of_cmd;
}				t_error;

typedef struct s_split
{
	char	*word;
	char	quote;
	int		par;
}				t_split;

typedef struct s_list_cmd
{
	struct s_list_cmd	*next;
	struct s_cmd		*command;
}				t_list_cmd;

/* operators */
char	*handle_operator(t_cmd *cmd, char *s);
/* redirections */
char	*handle_in_redirections(t_cmd *cmd, t_split *split, char *s_orig);
char	*handle_out_redirections(t_cmd *cmd, t_split *split, char *s_orig);
/* init */
t_error	*init_error(void);
t_split	*init_split(void);
t_cmd	*init_cmd(int prev_cmd);
char	*get_next_cmd(char *s, char **env, t_cmd *cmd);
/* free */
void	free_t_cmd(t_cmd *cmd);
/* error */
int		check_syntax(char *str);
int		check_start_or(char *str);
int		check_start_and(char *str);
char	*check_syntax_operator(char *str);
/* parsing utils */
char	*file_error(void);
void	cmd_list_add_char(t_cmd *cmd, t_split *split, char *s);
/* wildcards */
bool	is_indir(char *str);
bool	expand_wildcards(char *prefix, char **suffix, t_cmd *cmd);
void	handle_wildcards(t_cmd *cmd);
int		get_next_star_index(char *str);
char	**get_exp_list(char *start, char *end);
char	**lst_del(char **lst, int n);
int		get_nb_star(char *s);
char	**wildcard_split(char *s);
char	**init_f_list(void);
bool	is_in_list(char *str, char **lst);

#endif
