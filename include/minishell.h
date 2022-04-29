/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:18:55 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/08 12:18:57 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"
# include "pipex.h"

enum
{
	NONE,
	PIPE,
	AND,
	OR
};

enum
{
	FILE_ERROR = 127,
	PARSING_ERROR = 258
};

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			*here_doc;
	uint			mode;
	char			**cmd;
	int				exit_value;
}				t_cmd;

typedef struct s_split
{
	char	*word;
	char	quote;
	int		par;
}				t_split;

/* utils */
void	free_str_list(char **list);
void	free_t_cmd(t_cmd *cmd);
char	**add_string(char **lst1, char *str);
char	*add_char(char *str1, char c);
/* parsing */
char	*handle_operator(t_cmd *cmd, char *s);
char	*handle_in_redirections(t_cmd *cmd, t_split *split, char *s_orig);
char	*handle_out_redirections(t_cmd *cmd, t_split *split, char *s_orig);
t_split	*init_split(void);
t_cmd	*init_cmd(void);
t_cmd	*sh_split(char **s);
/* exec */
char	*get_path(char *cmd, char **envp);

/* test */
void	print_list(char **lst);
void	print_cmd_args(t_cmd *cmd);

/* pipex */
int		cmd_and(void);

#endif
