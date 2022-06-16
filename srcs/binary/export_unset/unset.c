/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:26:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/16 12:47:49 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_count_include_av(char **split, char **argv, int *argc)
{
	int	i;
	int	k;

	k = 1;
	while (argv[k])
	{
		i = 0;
		while (split[i])
		{
			if (!ft_memcmp(argv[k], split[i], ft_strlen(argv[k])))
				(*argc)++;
			i++;
		}
		k++;
	}
}//   argv == 5, real_argv_inside_export\envp == 3  [len]++[huy]++[priv]-[chel]-[kek]++ == 3

static void	ft_deleter_unset(char **av, char **split, char **ret)
{// if str is delete -> not strdup
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
	}//[life][kek][jojo][koko][\0] av[koko][\0] || av[jojo][\0]
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
	real_len = len_array - minus_strs; //new strings - all_unset_string
	ret = (char **)ft_calloc(sizeof(char *), real_len + 1);
	ft_deleter_unset(s->argv, s->export, &(*ret));
	s->export = ret;
	minus_strs = 0;
	len_array = ft_spllen(s->envp);
	ft_count_include_av(s->envp, s->argv, &minus_strs);
	real_len = len_array - minus_strs; //new strings - all_unset_string
	ret = (char **)ft_calloc(sizeof(char *), real_len + 1);
	ft_deleter_unset(s->argv, s->envp, &(*ret));
	s->envp = ret;
}

int	ft_unset(t_src *s)
{// copy envp and export, without argv[i]
	int		i;
	int		arg_count;

	if (1 == s->argc)
		return (1);
	i = 1;// 0[export] 1[word1] 2[word2] 3[\0]
	arg_count = (s->argc - 1);// -1 need to cut this ->1[export]<- 2[Ti ochen krasivaya] 3[another word]
	while (arg_count)
	{
		if (!ft_isalpha(s->argv[i][0]))// if argv == [987SLOVO]
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
