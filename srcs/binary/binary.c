/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:28:38 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/16 19:33:02 by mtiesha          ###   ########.fr       */
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

static void	ft_exec_redir(char **s)
{
	int		i;
	char	*ptr;
	char	*str;

	str = (*s);
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i + 1] \
			&& '.' == str[i] && '/' == str[i + 1])
		{
			str = ft_chardel(&str, i);
			str = ft_chardel(&str, i);
		}
		if (str[i] && str[i + 1] && str[i + 2] \
			&& '.' == str[i] && '.' == str[i + 1] && '/' == str[i + 2])
		{
			ptr = ft_strndup(str + 2, \
				ft_strlen(str + 2) - ft_strrnlen(str + 2, '/'));
			free(str);
			str = ptr;
		}
		i++;
	}
}

char	*ft_prepare_path(const char *av)
{
	char	*filename;
	char	*path;
	char	*ptr;
	int		i;

	i = 0;
	path = NULL;
	filename = ft_strdup(1 + ft_strrchr(av, '/'));
	while (av[i])
	{
		if (av[i] == '/')
		{
			if (i > 0 && path)
				free(path);
			path = ft_strndup((char *)(av), i);
		}
		i++;
	}
	ft_exec_redir(&path);
	ptr = ft_strjoinchar(path, filename, '/');
	free(filename);
	free(path);
	return (ptr);
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

static int	ft_exec_bash(t_src *s, const char *str)
{
/*	char	**av;
	char	*path;
	char	*ptr;
	pid_t	pid;

	av = ft_split(str, ' ');
	path = ft_prepare_path((const char *)(av[0]));
	ptr = ft_strdup(ft_strrchr(av[0], '/'));
	free(av[0]);
	av[0] = ptr;
	pid = fork();
	signal(SIGINT, ft_sig_handler_b);
	signal(SIGQUIT, ft_sig_handler_b);
	if (-1 == pid)
	{
		free(path);
		ft_splfree(av);
		return (1 && ft_putendl_fd("Fork error [bsh]", 2));
	}*/
	char	buff[4097];
	char	*path;
	char	**av;

	av = ft_split(str, ' ');
	if (ft_memcmp(str, "/", 1))
		str += (!ft_memcmp(str, "./", 2)) ? 2 : 0;
	path = getcwd(buff, 4096);
	set_path((char *)(str), &path);
	if (!fork())
	{
		signal(SIGINT, ft_sig_handler_b);
		signal(SIGQUIT, ft_sig_handler_b);
		if (-1 == execve(path, av, s->export))
		{
			ft_putstr_fd((char *)(str), 2);
			perror(": ");
			free(path);
			free(av);
			return (127);
		}
	}
	else
		wait(&s->ret);
	return (s->ret);
}

int	ft_isbuildin(char *str)
{
	char	*ptr;
	int		buildin;

	ptr = ft_strchr(str, '|');
	buildin = 0;
	if (!ft_memcmp(str, "env", 4) \
		|| !ft_memcmp(str, "exit", 5) \
		|| !ft_memcmp(str, "export", 7) \
		|| !ft_memcmp(str, "unset", 6) \
		|| !ft_memcmp(str, "echo", 5) \
		|| !ft_memcmp(str, "pwd", 4) \
		|| !ft_memcmp(str, "cd", 3) \
		|| ('.' == str[0] || '/' == str[0]))
		buildin = 1;
	if (!ptr && buildin)
	{
		printf("---------is buildin\n");
		return (1);
	}
	return (0);
}

int	ft_gate_binary(t_src *s)
{
	char	cwd[4097];
	int		i;
	int		bash;

	i = 0;
	bash = ft_get_minmax(('.' == s->argv[0][0]), ('/' == s->argv[0][0]), "max");// maybe del bash else
	printf("+++++====del if 0 or 1====++++++getminmax return:%d\n", bash);
	if (!ft_memcmp(s->argv[0], "env", 4))
		while (s->envp[i])
			ft_putendl_fd(s->envp[i++], 1);
	else if (!ft_memcmp(s->argv[0], "exit", 5))
		s->ret = ft_exec_exit(s);
	else if (!ft_memcmp(s->argv[0], "export", 7) \
			|| !ft_memcmp(s->argv[0], "unset", 6))
		s->envp = ft_gate_uns_expo(s);
	else if (!ft_memcmp(s->argv[0], "echo", 5))
		s->ret = ft_exec_echo(s, 1);
	else if (!ft_memcmp(s->argv[0], "pwd", 4))
		ft_putendl_fd(getcwd(cwd, 4096), 1);
	else if (!ft_memcmp(s->argv[0], "cd", 3))
		s->ret = ft_exec_cd(s);
	else if (bash)
		s->ret = ft_exec_bash(s, (const char *)(s->argv[0]));
	return (s->ret);
}
