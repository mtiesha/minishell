/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:40:45 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 11:15:17 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_free_src(t_src *s)
{
	if (s->envp)
		ft_splfree(s->envp);
	if (s->argv)
		ft_splfree(s->argv);
	if (s->export)
		ft_splfree(s->export);
	if (s->cmds)
		ft_splfree(s->cmds);
	if (s->str)
		free(s->str);
	free(s);
}

static void	ft_exit_norm(t_src **s)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (1 < (*s)->argc)
	{
		while (ft_isdigit((*s)->argv[1][i]))
			i++;
		if ((*s)->argv[1][i])
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd((*s)->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			(*s)->ret = 128;
			i = 128;
		}
		else
			i = ft_atoi((*s)->argv[1]);
	}
	ft_free_src((*s));
	if (i > 255)
		i = 128;
	exit(i);
}

int	ft_exec_exit(t_src *s)
{
	if (s->argc <= 2)
		ft_exit_norm(&s);
	else
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		s->ret = 128;
	}
	return (s->ret);
}
