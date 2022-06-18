/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:28:38 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/18 08:54:01 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_gate_uns_expo(t_src *s)
{
	if (!ft_memcmp(s->argv[0], "export", 7))
	{
		if (1 == s->argc)
			s->ret = ft_sort_env(s->export);
		else
			s->ret = ft_export_add(s);
	}
	else
		s->ret = ft_unset(s);
	return (s->envp);
}

int	ft_isbuildin(char *str)
{
	char	*ptr;
	int		buildin;

	ptr = ft_strchr(str, '|');
	buildin = 0;
	printf("BUILDINstr:+%s+\n", str);
	if (!ft_strncmp(str, "env", 3) \
		|| !ft_strncmp(str, "exit", 6) \
		|| !ft_strncmp(str, "export", 7) \
		|| !ft_strncmp(str, "unset", 5) \
		|| !ft_strncmp(str, "echo", 4) \
		|| !ft_strncmp(str, "pwd", 3) \
		|| !ft_strncmp(str, "cd", 2) \
		|| ('.' == str[0] || '/' == str[0]))
		buildin = 1;
	if (!ptr && buildin)
	{
		printf("---------is buildin\n");
		return (1);
	}
	printf("----------NOT_BUILDIN\n");
	return (0);
}

int	ft_gate_binary(t_src *s)
{
	char	cwd[4097];
	int		i;
	int		bash;

	i = 0;
	bash = ft_get_minmax(('.' == s->argv[0][0]), ('/' == s->argv[0][0]), "max");
	printf("====get_min_max: %d\n", bash);
	if (!ft_memcmp(s->argv[0], "env", 3))
		while (s->envp[i])
			ft_putendl_fd(s->envp[i++], 1);
	else if (!ft_memcmp(s->argv[0], "exit", 4))
		s->ret = ft_exec_exit(s);
	else if (!ft_memcmp(s->argv[0], "export", 6) \
			|| !ft_memcmp(s->argv[0], "unset", 5))
		s->envp = ft_gate_uns_expo(s);
	else if (!ft_memcmp(s->argv[0], "echo", 4))
		s->ret = ft_exec_echo(s, 1);
	else if (!ft_memcmp(s->argv[0], "pwd", 3))
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	else if (!ft_memcmp(s->argv[0], "cd", 2))
		s->ret = ft_exec_cd(s);
	else if (bash)
		s->ret = ft_exec_bash(s, (const char **)(s->argv));
	return (s->ret);
}
