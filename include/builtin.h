/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:45 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/13 00:21:18 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define EXIT_CODE -19

typedef struct s_cmd		t_cmd;

void	change_directory(char **cmd, char **env);
void	echo(char **cmd);
char	**export(char *cmd, char **env);
char	**unset(char *var, char **env);
void	ft_env(char **env);
void	pwd(void);
void	ft_exit(t_cmd *cmd);
void	try_exit(t_cmd *cmd, t_cmd *prev_cmd, char *str);

#endif
