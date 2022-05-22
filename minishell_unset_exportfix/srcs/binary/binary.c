/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:28:38 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/21 19:18:07 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
	if we have 0=[export] 1=[\0]
	we do ft_sort_envp
*/

static char	**multiple_env(t_data *src)
{
	src->ret = 0;
	if (!ft_memcmp(src->argv[0], "export", 7))
	{
		if (1 == src->argc)
			ft_sort_env(src->export);
		else
			ft_export_add(src);
	}
	else
		ft_unset(src);
	//src->ret = src->ret ? 1 : 0;
	return (src->envp);
}

static void	ft_print_env(t_data *src, int fd)
{
	int	i;

	i = 0;
	while (src->envp[i])
	{
		ft_putstr_fd(src->envp[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

static int	ft_ishuyznaet( t_data *src, int fd)//rename
{
	char	cwd[4097];

	if (!ft_memcmp(src->argv[0], "echo", 5))
		ft_exec_echo(src, fd);
	else if (!ft_memcmp(src->argv[0], "pwd", 4))
	{
		ft_putstr_fd(getcwd(cwd, 4096), fd);
		ft_putstr_fd("\n", fd);
	}
	else if (!ft_memcmp(src->argv[0], "cd", 3))
		ft_exec_cd(src);
	else
		return (0);
	return (1);
}

int	ft_gate_command(t_data *src, int fd)
{
	src->ret = 0;
	if (ft_ishuyznaet(src, fd))
		return (src->ret);
	else if (!ft_memcmp(src->argv[0], "env", 4))
		ft_print_env(src, fd);
	else if (!ft_memcmp(src->argv[0], "exit", 5))
		ft_exec_exit(src);
	else if (!ft_memcmp(src->argv[0], "export", 7) \
			|| !ft_memcmp(src->argv[0], "unset", 6))
		src->envp = multiple_env(src);
	else if (!ft_memcmp(src->argv[0], "./", 2) \
			|| !ft_memcmp(src->argv[0], "../", 3) \
			|| !ft_memcmp(src->argv[0], "/", 1))
		bash_command(src);
	else
		return (127);
	return (src->ret);
}
