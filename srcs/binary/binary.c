/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:28:38 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 18:44:03 by mtiesha          ###   ########.fr       */
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
	char	*pipe;
	char	*ptr;
	int		buildin;

	pipe = ft_strchr(str, '|');
	ptr = ft_strdup(str);
	ptr = ft_charadd(&ptr, ft_strlen(ptr), ' ');
	buildin = 0;
	if (!ft_strncmp(ptr, "env ", 4) \
		|| !ft_strncmp(ptr, "exit ", 5) \
		|| !ft_strncmp(ptr, "export ", 7) \
		|| !ft_strncmp(ptr, "unset ", 6) \
		|| !ft_strncmp(ptr, "echo ", 5) \
		|| !ft_strncmp(ptr, "pwd ", 4) \
		|| !ft_strncmp(ptr, "cd ", 3) \
		|| ('.' == ptr[0] || '/' == ptr[0]))
		buildin = 1;
	if (!pipe && buildin)
	{
		free(ptr);
		printf("----------IS_BUILDIN\n");
		return (1);
	}
	free(ptr);
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
	else if (!ft_memcmp(s->argv[0], "pwd", 3))
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	else if (!ft_memcmp(s->argv[0], "cd", 2))
		s->ret = ft_exec_cd(s);
	else if (bash)
		s->ret = ft_exec_bash(s, (const char **)(s->argv));
	return (s->ret);
}
