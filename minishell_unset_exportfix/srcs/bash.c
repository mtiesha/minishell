/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:38:25 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/20 18:32:11 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_errno(t_data *src, char *str)
{
	if (errno == ENOENT || errno == EACCES)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		if (errno == ENOENT)
			src->ret = 127;
		else
			src->ret = 126;
		return (1);
	}
	return (0);
}

static void	check_type(t_data *src, char *str, char *path)
{
	DIR			*dir;
	int			fd;
	char		**cmds;

	if (check_errno(src, str))
		return ;
	else if (!(dir = opendir(path)))
	{
		fd = open(path, O_RDONLY, 0666);
		free(src->str);
		while (ft_gnl_sh(&(src->str), 10000, fd))
		{
			cmds = src->cmds;
			parser(src);
			src->cmds = cmds;
		}
		close(fd);
	}
	else
	{
		ft_putstr_fd("-bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Is a directory", 2);
		src->ret = 126;
		closedir(dir);
	}
}

static void	set_filename(int len, char **new, char *str)
{
	int		i;
	char	*filename;
	char	*aux;

	i = 0;
	while (!ft_memcmp(str + i, "../", 3))
		i += 3;
	filename = ft_strdup(str + i);
	i /= 3;
	while (i-- > 0)
	{
		while ((*new)[len] != '/')
			len--;
		len--;
	}
	aux = ft_strndup(*new, len);
	free(*new);
	*new = ft_strjoin(aux, "/");
	free(aux);
	aux = ft_strjoin(*new, filename);
	free(*new);
	*new = aux;
	free(filename);
}

static void	set_path(char *str, char **path)
{
	int		len;
	char	*new;

	new = ft_strdup(*path);
	len = ft_strlen(*path);
	if (!ft_memcmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		set_filename(len, &new, str);
		*path = new;
		return ;
	}
	free(new);
}

void	bash_command(t_data *src)
{
	char	buff[4097];
	char	*path;
	char	*start;

	start = src->argv[0];
	if (ft_memcmp(src->argv[0], "/", 1))
		src->argv[0] += (!ft_memcmp(src->argv[0], "./", 2)) ? 2 : 0;
	path = getcwd(buff, 4096);
	set_path(src->argv[0], &path);
	if (!fork())
	{
		signal(SIGINT, child_sig_handler_bash);
		if (execve(path, src->argv, src->envp))
			check_type(src, start, path);
		exit(src->ret);
	}
	else
		wait(&src->ret);
	src->ret /= 256;
	free(path);
	src->argv[0] = start;
}
