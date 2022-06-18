/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:13:42 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/17 18:45:47 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_error(t_src *s)
{
	ft_putstr_fd("bash: cd: ", 2);
	if (2 != s->argc && 1 != s->argc)
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(s->argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		s->ret = 1;
	}
}

int	ft_change_envp(t_src *s, char *path)
{
	char	cwd[4097];
	char	oldpwd[4097];
	char	**env_ptr;
	int		i;

	i = 0;
	getcwd(oldpwd, 4096);// get current working dirrectory
	if ((2 == s->argc || 1 == s->argc) && !chdir(path))// change working directory
	{
		getcwd(cwd, 4096);// get actual working directory, after change
		env_ptr = s->envp;
		while (env_ptr[i] && ft_memcmp(env_ptr[i], "OLDPWD", 6))
			i++;
		free(env_ptr[i]);
		env_ptr[i] = ft_strjoin("OLDPWD=", oldpwd);
		i = 0;
		while (env_ptr[i] && ft_memcmp(env_ptr[i], "PWD", 3))
			i++;
		free(env_ptr[i]);
		env_ptr[i] = ft_strjoin("PWD=", cwd);
	}
	else
		ft_print_error(s);
	return (s->ret);
}

int	ft_exec_cd(t_src *s)
{// argc = [1] || [2] argv = [cd] || [cd] || [cd] [libft]
	char	*path;

	printf("__________CD____________\n");
	printf("ac:%d av0:+%s+\n", s->argc, s->argv[0]);
	if (1 == s->argc)
	{
		path = ft_get_strnspl(s->envp, "HOME", '=');
		if (!path)
		{
			s->ret = 1;
			ft_putendl_fd("cd: HOME not set", 2);
			return (s->ret);
		}
		path += 5;
	}
	else
		path = s->argv[1];
	s->ret = ft_change_envp(s, path);
	return (s->ret);
}
