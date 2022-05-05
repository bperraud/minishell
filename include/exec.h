/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 08:55:02 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/01 02:37:10 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd	t_cmd;


/* exec */

int		launch_cmd(t_cmd *command, char **envp);
void	exec_cmd(char **cmd_arg, char **envp);
int		extern_cmd(t_cmd *command, char**envp);

/* main loop */
int		start(int argc, char **argv, char **envp);
void	start_shell(char **envp, char *str_c);
void	sh(char *str, char **envp);

#endif
