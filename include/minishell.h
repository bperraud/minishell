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
	char			*infile;
	char			*outfile;
	bool			here_doc;
	bool			append_out;
	uint			mode;
	char			*var;
	char			*value;
	char			**cmd;
	struct s_cmd	*next;
}				t_cmd;

/* utils */
void	free_str_list(char **list);
char	**add_string(char **lst1, char *str);
char	*add_char(char *str1, char c);
/* parsing */
t_cmd	*sh_split(char *s);
t_cmd	*init_cmd(void);
/* exec */
void	sh(char *str);
char	*get_path(char *cmd, char **envp);

/* test */
void	print_list(char **lst);
#endif
