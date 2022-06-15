/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:28:38 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/15 13:39:25 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_gate_uns_expo(t_src *s)
{
	s->ret = 0;
	if (!ft_memcmp(s->argv[0], "export", 7))
	{
		if (1 == s->argc)
			ft_sort_env(s->export);
		else
			ft_export_add(s);
	}
	else
		ft_unset(s);
	if (s->ret)
		s->ret = 1;
	else
		s->ret = 0;
	return (s->envp);
}

static int	ft_exec_msh(t_src *s)
{
	// char	*path;
	// char	**cmd;
	// char	cwd[4097];
	(void)(s);
	return (0);
}

int	ft_gate_binary(t_src *s)
{
	char	cwd[4097];
	char	*ptr;
	int		i;

	i = 0;
	ptr = ft_strnstr(s->argv[0], "/minishell", ft_strlen(s->argv[0]));
	if (!ft_memcmp(s->argv[0], "env", 4))
		while (s->envp[i])
			ft_putendl_fd(s->envp[i++], 1);
	else if (!ft_memcmp(s->argv[0], "exit", 5))
		ft_exec_exit(s);
	else if (!ft_memcmp(s->argv[0], "export", 7) \
			|| !ft_memcmp(s->argv[0], "unset", 6))
		s->envp = ft_gate_uns_expo(s);
	else if (!ft_memcmp(s->argv[0], "echo", 5))
		ft_exec_echo(s, 1);
	else if (!ft_memcmp(s->argv[0], "pwd", 4))
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	else if (!ft_memcmp(s->argv[0], "cd", 3))
		ft_exec_cd(s);
	else if (ptr)
		ft_exec_msh(s);
	else
		s->ret = 127;
	return (s->ret);
}
