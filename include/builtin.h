/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:45 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/03 19:06:46 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	change_directory(char **cmd, char **env);
void	echo(char **cmd);
char	**export(char *cmd, char **env);
void	ft_env(char **env);

#endif
