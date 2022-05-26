/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:40:45 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/20 19:49:32 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_free_src(t_data *src)
{
	if (src->envp)
		ft_splfree(src->envp);
	if (src->argv)
		ft_splfree(src->argv);
	if (src->export)
		ft_splfree(src->export);
	if (src->cmds)
		ft_splfree(src->cmds);
	if (src->str)
		free(src->str);
	free(src);
}

static void	ft_exit_norm(t_data **src)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (1 < (*src)->argc)
	{
		while (ft_isdigit((*src)->argv[1][i]))
			i++;
		if ((*src)->argv[1][i])// if ![\0]
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd((*src)->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			(*src)->ret = 2;
			i = 2;
		}
		else
			i = ft_atoi((*src)->argv[1]);
	}
	ft_free_src((*src));
	exit(i);
}

void	ft_exec_exit(t_data *src)
{
	if (src->argc <= 2)
		ft_exit_norm(&src);
	else
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("bash: exit: too many arguments", 2);
		src->ret = 1;
	}
}
