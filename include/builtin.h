/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:45 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/14 23:29:04 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define EXIT_CODE -19

typedef struct s_cmd		t_cmd;

/* builtin */
char	**change_directory(t_cmd *command, char **env);
void	echo(char **cmd);
char	**export(char **cmd, char **env);
char	**unset(char **cmd, char **env);
void	pwd(void);

/* env */
void	ft_env(char **env);
void	ft_env_export(char **env);

/* exit */
void	ft_exit(t_cmd *cmd);
void	try_exit(t_cmd *cmd, char *str, char **envp);

#endif
