/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:24:24 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 08:33:48 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_alpha_add_dir_sec(t_src *s, char **sorted, char **strs, int i)
{
	int		k;
	char	*ptr;

	k = 0;
	(*sorted) = ft_strndup(ft_get_strnspl(s->argv, s->export[i], '='), \
		1 + ft_strnlen(ft_get_strnspl(s->argv, s->export[i], '='), '='));
	printf("first str: %s\n", (*sorted));
	while (k < ft_spllen(strs))
	{
		ptr = (*sorted);
		(*sorted) = ft_strjoin(ptr, strs[k++]);
		free(ptr);
		ptr = NULL;
		if (k < ft_spllen(strs))
		{
			ptr = (*sorted);
			(*sorted) = ft_strjoin(ptr, ":");
			free(ptr);
		}
	}
	ft_splfree(strs);
}

static void	ft_alpha_add_dir(t_src *s, char ***ret, int i)
{
	char	**strs;
	char	*sorted;
	char	*tmp;
	int		k;

	tmp = ft_strdup(ft_get_strnspl(s->argv, s->export[i], '='));
	if (ft_iscinstr(tmp, ':'))
	{
		k = 1 + ft_strnlen(tmp, '=');
		strs = ft_split(tmp + k, ':');
		ft_putspl_fd(strs, 2);
		k = 0;
		while (k < ft_spllen(strs))
		{
			if (ft_strncmp(strs[k], strs[k + 1], ft_strlen(strs[k])) > 0)
				ft_swap_ptr(&strs[k], &strs[k + 1]);
			k++;
		}
		ft_alpha_add_dir_sec(s, &sorted, strs, i);
		free(tmp);
	}
	else
		sorted = tmp;
	(*ret)[i] = ft_strdup(sorted);
	free(sorted);
}

static void	ft_norm_export(t_src *s, char **ret, int i, int j)
{
	int	arg_count;

	i = 0;
	j = 1;
	arg_count = s->argc - 1;
	while (i < ft_spllen(s->export))
	{
		if (ft_get_strnspl(s->argv, s->export[i], '='))
			ft_alpha_add_dir(s, &ret, i);
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
		if (!ft_isalpha(s->argv[i][0]) || !ft_iscinstr(s->argv[i], '='))
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
