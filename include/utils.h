/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:05:47 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/01 02:57:21 by bperraud         ###   ########.fr       */
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

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define RESET "\e[0m"

enum	e_file
{
	READ,
	WRITE
};

/* list */
void	lstcpy(char **dst, char **src);
int		lst_len(char **lst);
void	free_str_list(char **list);

/* utils */
char	*ft_sstrdup(char *src);
char	*ft_strndup(char *src, int n);
void	*smalloc(size_t n_bytes);
char	**add_string(char **lst1, char *str);
char	*add_multiple_chars(char *s1, char *s2);
char	*add_char(char *str1, char c);

/* shell_utils */
int		exit_to_bash_code(int exit_code);
int		free_and_return(char *str, void *ptr, int r_value);
char	*skip_spaces(char *str);
int		test_access(char *str, int file_access);

/* env */
char	*ft_getenv(char *str, char **env);
char	*get_var_value(char *str);
char	**env_unset(char *var, char **env);
char	**env_add(char **env, char *new_var);
char	**env_dup(char **envp);

/* env utils */
int		get_var_len(char *s);

/* prompt */
char	*print_prompt(char *color);
char	*error_to_color(void);

#endif
