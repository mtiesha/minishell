/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:24:24 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/04 19:53:51 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_isinside(char **export, char *str)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (!ft_memcmp(export[i], str, ft_strlen(export[i])))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_norm_export(t_src *s, char **ret)
{
	int	i;
	int	j;
	int	arg_count;

	i = 0;
	j = 1;
	arg_count = s->argc - 1;
	while (s->export[i])
	{
		ret[i] = ft_strdup(s->export[i]);
		i++;
	}
	while (arg_count)
	{
		if (!ft_isinside(s->export, s->argv[j]))
		{
			ret[i] = ft_strdup(s->argv[j]);
			i++;
		}
		j++;
		arg_count--;
	}
	ft_splfree(s->export);
	s->export = ret;
}

void	ft_export_add(t_src *s)
{// need add check if is include
	char	**ret;
	int		i;
	int		arg_count;

	i = 1;// 0[export] 1[word1] 2[word2] 3[\0]
	arg_count = (s->argc - 1);// -1 need to cut this -> 1[export] <- 2[Ti ochen krasivaya] 3[another word]
	while (arg_count)
	{
		if (!ft_isalpha(s->argv[i][0]))// if argv == [987SLOVO]
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(s->argv[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return ;
		}
		arg_count--;
		i++;
	}
	arg_count = 0;
	ft_count_include_av(s->export, s->argv, &arg_count);
	i = (s->argc - 1 - arg_count) + ft_spllen(s->export); //new strings + all_export_string
	ret = (char **)ft_calloc(sizeof(char *), i + 1);
	ft_norm_export(s, &(*ret));
}
