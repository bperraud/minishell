/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:18:55 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/03 17:37:30 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "parsing.h"
# include "exec.h"
# include "builtin.h"
# include "utils.h"
# include "pipex.h"
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>

# define STDIN 0
# define STDOUT 1

# define OR_MODE_ERROR -1

extern int	g_error;

enum e_error
{
	FILE_ERROR = 1,
	NOT_EXECUTABLE = 126,
	COMMAND_NOT_FOUND = 127,
	INTERRUPTED = 130,
	QUIT = 131,
	SYNTAX_ERROR = 258
};

/* signals */
void	sig_handler(void);
void	sig_exit(void);
void	term_config(void);

void	prompt_error(char *str, char *error);

#endif
