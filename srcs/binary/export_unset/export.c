/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:24:24 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/23 12:27:34 by mtiesha          ###   ########.fr       */
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

static void	ft_norm_export(t_data *src, char **ret)
{
	int	i;
	int	j;
	int	arg_count;

	i = 0;
	j = 1;
	arg_count = src->argc - 1;
	while (src->export[i])
	{
		ret[i] = ft_strdup(src->export[i]);
		i++;
	}
	while (arg_count)
	{
		if (!ft_isinside(src->export, src->argv[j]))
		{
			ret[i] = ft_strdup(src->argv[j]);
			i++;
		}
		j++;
		arg_count--;
	}
	ft_splfree(src->export);
	src->export = ret;
}

void	ft_export_add(t_data *src)
{// need add check if is include
	char	**ret;
	int		i;
	int		arg_count;

	i = 1;// 0[export] 1[word1] 2[word2] 3[\0]
	arg_count = (src->argc - 1);// -1 need to cut this -> 1[export] <- 2[Ti ochen krasivaya] 3[another word]
	while (arg_count)
	{
		if (!ft_isalpha(src->argv[i][0]))// if argv == [987SLOVO]
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(src->argv[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return ;
		}
		arg_count--;
		i++;
	}
	arg_count = 0;
	ft_count_include_av(src->export, src->argv, &arg_count);
	i = (src->argc - 1 - arg_count) + ft_spllen(src->export); //new strings + all_export_string
	ret = (char **)ft_calloc(sizeof(char *), i + 1);
	ft_norm_export(src, &(*ret));
}
