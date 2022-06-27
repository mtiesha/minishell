/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:38:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 11:34:23 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_change_path(int len, char **ret, char *str)
{
	int		i;
	char	*filename;
	char	*ptr;

	i = 0;
	if (str[i] != '/' && !ft_strncmp(str, "./", 2))
		i += 2;
	while (!ft_strncmp(str + i, "../", 3))
		i += 3;
	filename = ft_strdup(str + i);
	i /= 3;
	while (i-- > 0)
	{
		while ((*ret)[len] != '/')
			len--;
		len--;
	}
	ptr = ft_strndup(*ret, len);
	free(*ret);
	*ret = ft_strjoin(ptr, "/");
	free(ptr);
	ptr = ft_strjoin(*ret, filename);
	free(*ret);
	*ret = ptr;
	free(filename);
}

static void	ft_gate_change_path(char *str, char **path)
{
	char	*ret;
	int		len;

	len = ft_strlen(*path);
	ret = ft_strdup(*path);
	if (!ft_strncmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		ft_change_path(len, &ret, str);
		*path = ret;
		return ;
	}
	free(ret);
}

static void	ft_exit_error(char *str, char **av, char *path)
{
	if (str == NULL)
	{
		ft_splfree(av);
		free(path);
	}
	else
	{
		ft_putstr_fd(str, 2);
		perror(": ");
		ft_splfree(av);
		free(path);
		exit (126);
	}
}

int	ft_exec_bash(t_src *s, const char **str)
{
	char	**av;
	char	*path;
	char	tmp[4242];
	int		status;
	pid_t	pid;

	av = ft_spldup((char **)(str));
	path = getcwd(tmp, 4221);
	ft_gate_change_path((*av), &path);
	pid = fork();
	if (0 == pid)
	{
		ft_signal_cast(0);
		status = execve(path, av, s->export);
		if (-1 == status)
			ft_exit_error((char *)(*str), av, path);
	}
	else if (-1 != pid && 0 != pid)
		wait(&s->ret);
	ft_exit_error(NULL, av, path);
	return (s->ret);
}
