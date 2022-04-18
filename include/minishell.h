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
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "libft.h"

enum
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
	char			*infile;
	char			*outfile;
	char			*here_doc;
	bool			append_out;
	uint			mode;
	char			**cmd;
	struct s_cmd	*next;
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
t_split	*init_split(void);
t_cmd	*init_cmd(void);
t_cmd	*sh_split(char *s);
/* exec */
void	sh(char *str);
char	*get_path(char *cmd, char **envp);

/* test */
void	print_list(char **lst);
void	print_cmd_args(t_cmd *cmd);

#endif
