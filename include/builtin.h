/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 22:57:52 by bperraud          #+#    #+#             */
/*   Updated: 2022/04/30 22:57:52 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

/* cd */
int		change_directory(char **cmd);
int		echo(char **cmd);
int		unset(char **cmd);
int		export(char **cmd);
int		env();
int		pwd();

#endif
