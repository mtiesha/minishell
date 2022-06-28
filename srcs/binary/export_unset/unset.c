/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:26:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 13:34:11 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_count_include_av(char **split, char **argv, int *argc)
{
	int	i;
	int	k;

	k = 1;
	while (k < ft_spllen(argv))
	{
		i = 0;
		while (i < ft_spllen(split))
		{
			if (!ft_strncmp(argv[k], split[i], ft_strlen(argv[k])))
				(*argc)++;
			i++;
		}
		k++;
	}
}

static void	ft_deleter_unset(char **av, char **split, char **ret)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (split[i])
	{
		k = 1;
		while (av[k])
		{
			if (!ft_memcmp(av[k], split[i], ft_strnlen(av[k], '=')))
				break ;
			k++;
		}
		if (!av[k])
		{
			ret[j] = ft_strdup(split[i]);
			j++;
		}
		i++;
	}
	ft_splfree(split);
}

static void	ft_gate_unset(t_src *s)
{
	int		len_array;
	int		real_len;
	int		minus_strs;
	char	**ret;

	minus_strs = 0;
	len_array = ft_spllen(s->export);
	ft_count_include_av(s->export, s->argv, &minus_strs);
	real_len = len_array - minus_strs;
	ret = (char **)ft_calloc(sizeof(char *), real_len + 1);
	ft_deleter_unset(s->argv, s->export, &(*ret));
	s->export = ret;
	minus_strs = 0;
	len_array = ft_spllen(s->envp);
	ft_count_include_av(s->envp, s->argv, &minus_strs);
	real_len = len_array - minus_strs;
	ret = (char **)ft_calloc(sizeof(char *), real_len + 1);
	ft_deleter_unset(s->argv, s->envp, &(*ret));
	s->envp = ret;
}

int	ft_unset(t_src *s)
{
	int		i;
	int		arg_count;

	if (1 == s->argc)
		return (1);
	i = 1;
	arg_count = (s->argc - 1);
	while (arg_count)
	{
		if (!ft_isalpha(s->argv[i][0]))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(s->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		arg_count--;
		i++;
	}
	ft_gate_unset(s);
	return (0);
}
