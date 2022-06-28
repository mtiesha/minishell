/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:09:49 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 17:56:12 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_signal_cast(int switcher)
{
	if (1 == switcher)
	{
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_handler);
	}
	else if (0 == switcher)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
