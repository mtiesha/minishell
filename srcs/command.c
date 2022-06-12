/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:57:34 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/07 13:14:52 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	copy_args1(t_src *src)
{
	int		i;
	int		j;
	char	**args;

	args = (char **)ft_calloc(sizeof(char *), src->argc + 1);
	i = 0;
	j = 0;
	while (j < src->argc)
	{
		if (!ft_memcmp(src->argv[i], ">", 2) ||
			!ft_memcmp(src->argv[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(src->argv[i++]);
	}
	ft_splfree(src->argv);
	src->argv = args;
}

char	**check_command(char *str, t_src *src)
{
	src->ret = 0;
	if (src->argv[0] && *(src->argv[0]))
	{
		//copy_args1(src);
		//src->ret = ft_gate_command(src);
		if (src->ret == 127)
		{
			ft_putstr_fd(str, 1);
			ft_putendl_fd(": command not found.", 1);
			src->ret = 127;
		}
	}
	return (src->envp);
}
