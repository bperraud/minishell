/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:59:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/06/11 18:37:01 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_error = INTERRUPT_NL;
		ft_putchar_fd('\n', 1);
		print_prompt();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	exit_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("^C\n", 1);
		g_error = INTERRUPTED;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
		g_error = QUIT;
	}
	return ;
}

void	sig_exit(void)
{
	struct sigaction	sa;

	sa.sa_handler = exit_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	sig_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	term_config(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
