/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:24:24 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/20 14:12:06 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_norm_export(t_src *s, char **ret, int i, int j)
{
	int	arg_count;

	i = 0;
	j = 1;
	arg_count = s->argc - 1;
	while (s->export[i])
	{
		if (ft_get_strnspl(s->argv, s->export[i], '='))
			ret[i] = ft_strdup(ft_get_strnspl(s->argv, s->export[i], '='));
		else
			ret[i] = ft_strdup(s->export[i]);
		i++;
	}
	while (arg_count)
	{
		if (!ft_get_strnspl(s->export, s->argv[j], '='))
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

int	ft_export_add(t_src *s)
{
	char	**ret;
	int		i;
	int		arg_count;

	i = 1;
	arg_count = (s->argc - 1);
	while (arg_count)
	{
		if (!ft_isalpha(s->argv[i][0]))
		{
			ft_putstr_fd(s->argv[i], 1);
			return (1 && ft_putendl_fd(" :not a valid identifier [exp]", 1));
		}
		arg_count--;
		i++;
	}
	arg_count = 0;
	ft_count_include_av(s->export, s->argv, &arg_count);
	i = (s->argc - 1 - arg_count) + ft_spllen(s->export) - arg_count;
	ret = (char **)ft_calloc(sizeof(char *), i + 1);
	ft_norm_export(s, &(*ret), 0, 1);
	return (0);
}
