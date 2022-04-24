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

//pipex
int		multiple_cmd(int fd[3], int argc, char **argv, char **envp);
int		here_doc(char *limiter);
void	pipex(char *arg, char**envp);
void	exec_cmd(char *arg, char **envp);

//files
char	**parsing(char **envp);
char	*create_path(char *path, char *arg);
int		open_file(char *file);

// utils
char	*ft_strncpy_split(char *dest, const char *src, unsigned int n);
void	exit_error(char **cmd1, char **cmd2, char **path);
void	free_all(char **cmd1, char **cmd2, char **path);
void	free_tab(char **tab);

//split
char	**split_arg(char const *s, char c);

#endif
