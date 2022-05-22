/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:26:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/22 18:22:13 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_count_include_av(char **split, char **argv, int *argc)
{
	int	i;
	int	k;

	k = 1;
	while (argv[k])
	{
		printf("av: %s\n", argv[k]);
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
	int	k;

	i = 0;
	while (split[i])
	{
		k = 1;
		while (av[k])
		{
			if (!ft_memcmp(av[k], split[i], ft_strlen(av[k])))
				break ;
			k++;
		}
		if (!av[k])
			ret[i] = ft_strdup(split[i]);
		i++;
	}
	ft_splfree(split);
}

static void	ft_gate_unset(t_data *src)
{
	int		len;
	int		after_len;
	int		real_minus_strs;
	char	**ret_env;
	char	**ret_exp;

	real_minus_strs = 0;
	len = ft_spllen(src->export);
	ft_count_include_av(src->export, src->argv, &real_minus_strs);
	after_len = len - real_minus_strs; //new strings - all_unset_string
	ret_exp = (char **)ft_calloc(sizeof(char *), after_len + 1);
	ft_deleter_unset(src->argv, src->export, &(*ret_exp));
	src->export = ret_exp;
	real_minus_strs = 0;
	len = ft_spllen(src->envp);
	ft_count_include_av(src->envp, src->argv, &real_minus_strs);
	after_len = len - real_minus_strs; //new strings - all_unset_string
	ret_env = (char **)ft_calloc(sizeof(char *), after_len + 1);
	ft_deleter_unset(src->argv, src->envp, &(*ret_env));
	src->envp = ret_env;
}

void	ft_unset(t_data *src)
{// copy envp and export, without argv[i]
	int		i;
	int		arg_count;

	if (1 == src->argc)
		return ;
	i = 1;// 0[export] 1[word1] 2[word2] 3[\0]
	arg_count = (src->argc - 1);// -1 need to cut this ->1[export]<- 2[Ti ochen krasivaya] 3[another word]
	while (arg_count)
	{
		if (!ft_isalpha(src->argv[i][0]))// if argv == [987SLOVO]
		{
			ft_putstr_fd("bash: unset: `", 1);
			ft_putstr_fd(src->argv[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return ;
		}
		arg_count--;
		i++;
	}
	ft_gate_unset(src);
}
