/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <jboumal@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:30:25 by jboumal           #+#    #+#             */
/*   Updated: 2022/04/19 11:30:28 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_word(char **s)
{
	char	*word;
	char	quote;

	word = NULL;
	quote = '\0';
	while (**s && !ft_strchr(" |&><()", **s))
	{
		if ((**s == '\'' || **s == '\"') && quote == **s)
			quote = '\0';
		else if ((**s == '\'' || **s == '\"') && !quote)
			quote = **s;
		else
			word = add_char(word, **s);
		(*s)++;
	}
	if (!word)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	return (word);
}

static void	open_infile(t_cmd *cmd, t_split *split, bool here_doc_mode)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->here_doc)
	{
		free(cmd->here_doc);
		cmd->here_doc = NULL;
	}
	if (here_doc_mode)
		cmd->here_doc = split->word;
	else
	{
		cmd->fd_in = open(split->word, O_RDONLY);
		if (cmd->fd_in < 0)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		free(split->word);
	}
	split->word = NULL;
}

static char	*open_outfile(t_cmd *cmd, t_split *split, bool append_mode, char *s)
{
	char	*word;

	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (split->word)
	{
		cmd->cmd = add_string(cmd->cmd, split->word);
		split->word = NULL;
	}
	word = get_next_word(&s);
	if (!append_mode)
		cmd->fd_out = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->fd_out = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(word);
	if (cmd->fd_out < 0)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	return (s);
}

char	*handle_in_redirections(t_cmd *cmd, t_split *split, char *s_orig)
{
	char	*s;

	s = s_orig;
	if (split->quote || split->par)
		return (s_orig);
	while (*s == ' ')
		s++;
	if (*s == '<' && *(s + 1) == '<')
	{
		s += 2;
		open_infile(cmd, split, true);
		return (s);
	}
	else if (*s == '<')
	{
		s++;
		open_infile(cmd, split, false);
		return (s);
	}
	return (s_orig);
}

char	*handle_out_redirections(t_cmd *cmd, t_split *split, char *s_orig)
{
	char	*s;

	s = s_orig;
	if (split->quote || split->par)
		return (s_orig);
	if (*s == '>' && *(s + 1) == '>')
	{
		s += 2;
		while (*s == ' ')
			s++;
		s = open_outfile(cmd, split, true, s);
		return (s);
	}
	else if (*s == '>')
	{
		s++;
		while (*s && *s == ' ')
			s++;
		s = open_outfile(cmd, split, false, s);
		return (s);
	}
	(void)cmd;
	(void) open_outfile;
	return (s_orig);
}
