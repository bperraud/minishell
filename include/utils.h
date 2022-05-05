/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:05:47 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/29 09:05:49 by jboumal          ###   ########.fr       */
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
# include "libft.h"

# define YELLOW "\e[0;33m"
# define RESET "\e[0m"


/* list */
void	lstcpy(char **dst, char **src);
int		lst_len(char **lst);
void	free_str_list(char **list);

/* utils */
void	*smalloc(int n_bytes);
char	**add_string(char **lst1, char *str);
char	*add_char(char *str1, char c);

/* shell_utils */
int		exit_to_bash_code(int exit_code);
char	*skip_spaces(char *str);

/* env */
char	**env_dup(char **envp);
char	**env_add(char **env, char *new_var);
char	*get_var_value(char *str);

/* prompt */
char	*print_prompt(void);

#endif