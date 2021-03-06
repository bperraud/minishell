/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:30:25 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/15 12:13:19 by bperraud         ###   ########.fr       */
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
	return (word);
}

static char	*open_infile(t_cmd *cmd, t_split *split, bool heredoc_mode, char *s)
{
	char	*word;

	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->here_doc)
	{
		free(cmd->here_doc);
		cmd->here_doc = NULL;
	}
	if (split->word)
		cmd->cmd = add_string(cmd->cmd, split->word);
	split->word = NULL;
	word = get_next_word(&s);
	if (!word)
		return (s);
	if (heredoc_mode)
		cmd->here_doc = word;
	else
	{
		cmd->fd_in = open(word, O_RDONLY);
		if (cmd->fd_in < 0)
			file_not_found_error(word);
		free(word);
	}
	return (s);
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
	if (!word)
		return (s);
	if (test_access(word, WRITE))
	{
		free(word);
		return (NULL);
	}
	if (!append_mode)
		cmd->fd_out = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->fd_out = open(word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(word);
	if (cmd->fd_out < 0)
		return (file_error());
	return (s);
}

char	*handle_in_redirections(t_cmd *cmd, t_split *split, char *s_orig)
{
	char	*s;

	s = s_orig;
	if (split->quote || split->par)
		return (s_orig);
	if (*s == '<' && *(s + 1) == '<')
	{
		s += 2;
		while (*s && *s == ' ')
			s++;
		s = open_infile(cmd, split, true, s);
		return (s);
	}
	else if (*s == '<')
	{
		s++;
		while (*s && *s == ' ')
			s++;
		s = open_infile(cmd, split, false, s);
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
		while (*s == ' ')
			s++;
		s = open_outfile(cmd, split, false, s);
		return (s);
	}
	return (s_orig);
}
