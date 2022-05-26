/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:05:11 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/21 17:05:13 by mtiesha          ###   ########.fr       */
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

static void	init_param(t_data **src, char **argv, char **envp, int *ret_len)
{// add if (!dup)
	(*src) = (t_data *)malloc(sizeof(t_data));
	(*src)->envp = ft_spldup(envp);
	(*src)->argv = argv;
	(*src)->export = NULL;
	(*src)->export = ft_spldup(envp);
	(*src)->ret = 0;
	(*src)->str = 0;
	(*src)->child = 0;
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
	t_data	*src;
	int		ret_len[2];
	char	*promt;

	(void)(argc);
	init_param(&src, argv, envp, ret_len);
	while (1)
	{
		signal(SIGQUIT, ft_sig_handler);
		signal(SIGINT, ft_sig_handler);
		promt = ft_get_prompt(envp);
		src->str = readline(promt);
		free(promt);
		if (NULL != src->str)
		{
			if (!ft_is_here_doc(src->str))
				add_history(src->str);
			parser(src);
		}
		else if (NULL == src->str)
		{
			ft_putstr_fd("exit\n", 2);
			exit(src->ret);
		}
	}
	return (0);
}
