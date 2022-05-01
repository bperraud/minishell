/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:18:55 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/08 12:18:57 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "parsing.h"
# include "exec.h"
# include "utils.h"
# include "build_in.h"
# include "pipex.h"

enum e_error
{
	FILE_ERROR = 127,
	PARSING_ERROR = 258
};

/* test */
void	print_list(char **lst);
void	print_cmd_args(t_cmd *cmd);

#endif
