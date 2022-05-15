/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2022/05/13 13:07:26 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static char	*ft_get_prompt(char **envp)
{
	char	*home;
	char	*path;
	char	*c_path;
	char	cwd[4097];

	home = get_env(envp, "HOME");
	getcwd(cwd, 4096);
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	c_path = path;
	path = ft_strjoin("\033[32mGlina@minishell:\033[1;34m", c_path);
	free(c_path);
	c_path = path;
	path = ft_strjoin(c_path, "\033[0;0m$ ");
	free(c_path);
	return (path);
}

static void	ft_sig_handler(int sig)
{
	char	cwd[4097];
	char	*home;
	char	*current;

	if (sig == SIGINT)
	{
		getcwd(cwd, 4096);
		home = getenv("HOME");
		current = ft_strdup(cwd + ft_strlen(home));
		write(2, "\n", 1);
		ft_putstr_fd("\033[32mGlina@minishell:\033[1;34m~", 2);
		ft_putstr_fd(current, 2);
		ft_putstr_fd("\033[0;0m$ ", 2);
		free(current);
	}
}

static void	init_param(t_data **param, char **argv, char **envp, int *ret_len)
{
	(*param) = (t_data *)malloc(sizeof(t_data));
	(*param)->envp = copy_env(envp, 0);
	(*param)->export = (char **)ft_calloc(sizeof(char *), 1);
	(*param)->argv = argv;
	(*param)->ret = 0;
	(*param)->str = 0;
	(*param)->child = 0;
	ret_len[0] = 0;
}

static int	ft_is_here_doc(char *str)
{
	while (*str != '<' && *str)
		str++;
	if (*str == '<' && *(str + 1) == '<')
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*param;
	int		ret_len[2];
	char	*promt;

	(void)(argc);
	init_param(&param, argv, envp, ret_len);
	while (1)
	{
		signal(SIGQUIT, ft_sig_handler);
		signal(SIGINT, ft_sig_handler);
		promt = ft_get_prompt(envp);
		param->str = readline(promt);
		free(promt);
		if (NULL != param->str)
		{
			if (!ft_is_here_doc(param->str))
				add_history(param->str);
			parser(param);
		}
		else if (NULL == param->str)
		{
			ft_putstr_fd("exit\n", 2);
			exit(param->ret);
		}
	}
	return (0);
}
