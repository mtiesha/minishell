/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:36:37 by marvin            #+#    #+#             */
/*   Updated: 2022/05/20 18:40:04 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_in(char **argv)
{
	int		fd;
	int		i;

	i = 0;
	while (argv[i] && ft_memcmp(argv[i], "<", 2))
		i++;
	if (argv[i])
	{
		fd = open(argv[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putendl_fd("Couldn't read from file.", 2);
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

static void	exec_bin(int fd, char *path, t_data *src)
{
	char	**args;

	args = copy_args(src);
	signal(SIGINT, child_sig_handler);
	if (!fork())
	{
		set_in(src->argv);
		if (fd > 1)
			dup2(fd, 1);
		if ((execve(path, args, src->envp)) && errno == EACCES)
		{
			src->ret = 126;
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(src->argv[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		exit(src->ret);
	}
	wait(&src->ret);
	src->ret /= 256;
	free(path);
	ft_splfree(args);
}

static char	**split_path(t_data *src, char *str)
{
	char	*path;
	char	**paths;

	path = get_env(src->envp, "PATH");
	if (path)
		paths = ft_split(path, ':');
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		src->ret = 127;
		return (NULL);
	}
	return (paths);
}

static char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *src)
{
	char		**paths;
	char		*path;
	int			i;

	paths = split_path(src, str);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		while ((*dir) && errno != EACCES && (*d = readdir(*dir)))
		{
			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				ft_splfree(paths);
				return (path);
			}
		}
		closedir(*dir);
	}
	ft_splfree(paths);
	return (NULL);
}

int	check_bin(int fd, t_data *src)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	char			*path;

	src->ret = 127;
	pre_path = search_bin(src->argv[0], &dir, &d, src);
	if (pre_path)
	{
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fd, path, src);
		closedir(dir);
	}
	free(pre_path);
	return (src->ret);
}
