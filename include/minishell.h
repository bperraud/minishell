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
# include "libft.h"

# define FALSE 0
# define TRUE 1

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
	uint			here_doc;
	uint			append_out;
	uint			mode;
	char			**cmd;
	struct s_cmd	*next;
}				t_cmd;

/* utils */
void	free_str_list(char **list);
/* parsing */
t_cmd	*parse_cmd(char *str);
t_cmd	*init_cmd(void);
/* exec */
void	sh(t_cmd *cmd);
char	*get_path(char *cmd, char **envp);

#endif
