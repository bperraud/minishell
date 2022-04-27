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

# define FILE_NAME "temp/file"

typedef struct s_cmd t_cmd;

//start
int		start(int argc, char **argv, char **envp);

//pipex
int		multiple_cmd(int fd[3], int argc, char **argv, char **envp);
int		pipex(char **arg, char**envp);
void	which_cmd(char **cmd, char **envp);
int		cmd_pipe(t_cmd *command, char **envp);

//files
char	**parsing(char **envp);
char	*create_path(char *path, char *arg);
int		open_file(char *file);
void	dup_close(int fd, int std);
int		here_doc(char *limiter);

// utils
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
void	exit_error(char **cmd1, char **cmd2, char **path);
void	free_all(char **cmd1, char **cmd2, char **path);
void	free_tab(char **tab);

//split
char	**split_arg(char const *s, char c);

//execution
void	exec_cmd(char **cmd_arg, char **envp);

int		single_cmd(t_cmd *command, char**envp);


int		cmd_and(t_cmd *command, char **envp);


#endif
