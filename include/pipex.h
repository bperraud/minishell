/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:34:43 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/21 02:59:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "fcntl.h"
# include "sys/wait.h"
# include "errno.h"

# define HERE_DOC ".pipex.temp"

typedef struct s_cmd		t_cmd;
typedef struct s_list_cmd	t_list_cmd;

/* pipex */
void		pipe_cmd(char **str, char **envp, int fd_save[2], t_cmd **cmd);

/* files */
char		**parsing_path(char **envp);
char		*create_path(char *path, char *arg);
int			here_doc(char *limiter);
int			is_cmd_in_path(char *cmd, char **envp);

/* utils */
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
void		exit_error(char **cmd1, char **cmd2, char **path);
void		free_all(char **cmd1, char **cmd2, char **path);
void		free_tab(char **tab);

/* list_cmd */
void		print_cmd(t_list_cmd *list_cmd);
t_list_cmd	*lst_last(t_list_cmd *list_cmd);
void		add_back(t_list_cmd **list_cmd, t_cmd *new);
t_list_cmd	*init_list(void);
void		free_list_cmd(t_list_cmd *list_cmd);

#endif
