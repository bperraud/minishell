/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:55:02 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/17 16:42:49 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd	t_cmd;

/* subshell */
void	subshell(t_cmd **cmd, char **envp);

char	**command(t_cmd *cmd, char **envp);

/* exec */
char	**launch_cmd(t_cmd *command, char **envp);
void	exec_cmd(char **cmd_arg, char **envp);
void	extern_cmd(t_cmd *command, char**envp);

/* main loop */
int		start(int argc, char **argv, char **envp);
void	start_shell(char **envp, char *str_c);

/* executable */
void	ft_executable(char **cmd, char **envp);

#endif
