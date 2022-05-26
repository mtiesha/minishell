/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:13:42 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/18 16:17:25 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_error(t_data *src)
{
	ft_putstr_fd("bash: cd: ", 2);
	if (2 != src->argc && 1 != src->argc)
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(src->argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		src->ret = 1;
		errno = 0;
	}
}

static void	ft_change_envp(t_data *src, char *path)
{
	char	cwd[4097];
	char	oldpwd[4097];
	char	**env_ptr;
	int		i;

	i = 0;
	getcwd(oldpwd, 4096);// get current working dirrectory
	if ((2 == src->argc || 1 == src->argc) && !chdir(path))// change working directory
	{
		getcwd(cwd, 4096);// get actual working directory, after change
		env_ptr = src->envp;
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
		ft_print_error(src);
}

void	ft_exec_cd(t_data *src)
{// argc = [1] || [2] argv = [cd] || [cd] || [cd] [libft]
	char	*path;

	if (1 == src->argc)
		path = get_env(src->envp, "HOME");
	else
		path = src->argv[1];
	ft_change_envp(src, path);
}
