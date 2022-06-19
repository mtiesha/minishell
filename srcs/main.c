/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:05:11 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/19 13:44:30 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_get_prompt(char **envp)
{
	char	*home;
	char	*path;
	char	*c_path;
	char	cwd[4097];

	home = ft_get_strnspl(envp, "HOME", '=');
	getcwd(cwd, 4096);
	if (home)
	{
		home += 5;
		if (ft_strncmp(cwd, home, ft_strlen(home)))
			path = ft_strdup(cwd);
		else
			path = ft_strjoin("~", cwd + ft_strlen(home));
		c_path = path;
	}
	else
		c_path = ft_strdup(cwd);
	path = ft_strjoin("\033[32mGlina@minishell:\033[1;34m", c_path);
	free(c_path);
	c_path = path;
	path = ft_strjoin(c_path, "\033[0;0m$ ");
	free(c_path);
	return (path);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_cast(int switcher)
{
	if (1 == switcher)
	{
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_handler);
	}
	else if (0 == switcher)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

static void	ft_init(t_src **src, char **envp)
{
	(*src) = (t_src *)malloc(sizeof(t_src));
	(*src)->envp = NULL;
	(*src)->envp = ft_spldup(envp);
	//if (!(*src)->envp)
	//	ft_oshibochka_s_exitom();
	(*src)->argv = NULL;
	(*src)->export = NULL;
	(*src)->export = ft_spldup((*src)->envp);
	//if (!(*src)->export)
	//	ft_oshibochka_s_exitom();
	(*src)->str = NULL;
	(*src)->ret = 0;
	(*src)->child = 0;// maybe not use
}

int	main(int argc, char **argv, char **envp)
{
	t_src	*src;
	char	*promt;

	(void)(argc);
	(void)(argv);
	ft_init(&src, envp);
	while (1)
	{
		ft_signal_cast(1);
		promt = ft_get_prompt(envp);
		src->str = readline(promt);
		free(promt);
		if (NULL != src->str)
		{
			if (0 == ft_strncmp("d5", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    cat << STOP      | ls -l   -a | wc   -l |  cat >> f2   ");
			}
			else if (0 == ft_strncmp("d4", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    cat < Makefile    |  cat | wc   -l |  wc >> f2   ");
			}
			else if (0 == ft_strncmp("d3", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    cat < Makefile    |  cat | wc   -l |  wc > f2   ");
			}
			else if (0 == ft_strncmp("d2", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    cat < Makefile    |  cat | wc   -l    ");
			}
			else if (0 == ft_strncmp("d1", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    ls -l    -a   |  cat | wc   -l    ");
			}
			if (!ft_strnstr(src->str, "<<", ft_strlen(src->str)))
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
