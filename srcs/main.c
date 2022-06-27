/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:05:11 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 19:16:22 by mtiesha          ###   ########.fr       */
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
	path = ft_strjoin("\001\033[2;92m\002Glina@minishell:\001\033[2;94m\002", c_path);
	free(c_path);
	c_path = path;
	path = ft_strjoin(c_path, "\001\033[2;97m\002$ ");
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

static int	ft_init(t_src **src, char **envp)
{
	(*src) = (t_src *)malloc(sizeof(t_src));
	(*src)->envp = NULL;
	(*src)->envp = ft_spldup(envp);
	if (!(*src)->envp)
	{
		free(*src);
		return (0);
	}
	(*src)->argv = NULL;
	(*src)->export = NULL;
	(*src)->export = ft_spldup((*src)->envp);
	if (!(*src)->export)
	{
		ft_splfree((*src)->envp);
		free(*src);
		return (0);
	}
	(*src)->str = NULL;
	(*src)->ret = 0;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_src	*src;
	char	*promt;

	(void)(argc);
	(void)(argv);
	if (!ft_init(&src, envp))
		return (1 && ft_putendl_fd("Inicialization faild [mn]", 2));
	while (1)
	{
		ft_signal_cast(1);
		promt = ft_get_prompt(src->envp);
		src->str = readline(promt);
		free(promt);
		if (NULL != src->str)
		{
			if (0 == ft_strncmp("rm -rf *", src->str, 9))
			{
				ft_putendl_fd("Vse udaleno bezvozvratno", 2);
				return (0);
			}
			if (0 == ft_strncmp("d5", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    cat << STOP      | ls -l   -a | wc   -l |  cat >> f2   ");
			}
			else if (0 == ft_strncmp("d4", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup("    cat < Makefile    | < f3 cat | < f4 wc   -l > f7 |  wc >> f2   ");
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
			else if (0 == ft_strncmp("r1", src->str, 3))
			{
				free(src->str);
				src->str = ft_strdup(" < f2 < f4 <f5   <f53 ls   -la > f21 >f22 > f23 >f24    >f54   | <f21 < f222 < f49 < f55 wc -l > f7 > f8 >f9 > f56 ");
			}
			if (' ' != src->str[0] && src->str[0] \
				&& !ft_strnstr(src->str, "<<", ft_strlen(src->str)))
				add_history(src->str);
			src->ret = ft_lexer(src);
			if (0 == src->ret)
				parser(src);
		}
		else if (NULL == src->str)
		{
			ft_putendl_fd("exit", 2);
			exit(src->ret);
		}
	}
	return (0);
}
