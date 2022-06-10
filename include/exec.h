/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:55:02 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/10 16:15:37 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd	t_cmd;

/* subshell */
void	subshell(t_cmd *cmd,  int fd_save[2], char **envp);
char	**command(t_cmd *cmd,  int fd_save[2], char **envp);

/* exec */
void	extern_cmd(t_cmd *command, char**envp);

/* main loop */
int		start(int argc, char **argv, char **envp);
void	start_shell(char **envp, char *str_c);

/* executable */
void	ft_executable(char **cmd, char **envp);

/* redirection */
void	error_file_exit(char *error);
void	redirect(t_cmd *command, int fd_save[2]);
void	restore_std(int fd_save[2]);
void	dup_close(int fd, int std);

#endif
