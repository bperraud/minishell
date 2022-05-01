/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:05:47 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/01 00:32:36 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdarg.h>
# include "libft.h"

/* utils */
void	free_str_list(char **list);
char	**add_string(char **lst1, char *str);
char	*add_char(char *str1, char c);
int		ft_printf(const char *str, ...);

#endif
