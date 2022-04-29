/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:54:56 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/29 08:54:59 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
	unsigned int	mode;
	char			**cmd;
	int				exit_value;
}				t_cmd;

typedef struct s_split
{
	char	*word;
	char	quote;
	int		par;
}				t_split;

/* operators */
char	*handle_operator(t_cmd *cmd, char *s);
/* redirections */
char	*handle_in_redirections(t_cmd *cmd, t_split *split, char *s_orig);
char	*handle_out_redirections(t_cmd *cmd, t_split *split, char *s_orig);
/* init */
t_split	*init_split(void);
t_cmd	*init_cmd(void);
t_cmd	*sh_split(char **s);
/* free */
void	free_t_cmd(t_cmd *cmd);

#endif