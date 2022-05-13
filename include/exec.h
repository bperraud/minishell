/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:55:02 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/13 18:47:12 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd	t_cmd;

/* exec */
char	**launch_cmd(t_cmd *command, char **envp);
int		exec_cmd(char **cmd_arg, char **envp);
void	extern_cmd(t_cmd *command, char**envp);

/* main loop */
int		start(int argc, char **argv, char **envp);
void	start_shell(char **envp, char *str_c);
char	**sh(char *str, char **envp);

/* executable */
void	ft_executable(char **cmd, char **envp);

#endif
