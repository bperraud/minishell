/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:45 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/12 01:26:06 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	change_directory(char **cmd, char **env);
void	echo(char **cmd);
char	**export(char *cmd, char **env);
char	**unset(char *var, char **env);
void	ft_env(char **env);
void	pwd(void);

#endif
