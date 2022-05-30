/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:59:49 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/30 15:38:31 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		print_prompt(error_to_color());
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd(GREEN, 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd(RESET, 1);
	}
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
