/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:55:59 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 07:15:58 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_print_sorted(char **sorted)
{
	int	i;
	int	len;

	i = 0;
	while (i < ft_spllen(sorted))
	{
		len = ft_strnlen(sorted[i], '=');
		ft_putstr_fd("declare -x ", 1);
		ft_putnstr_fd(sorted[i], len, 1);
		if ('=' == sorted[i][len])
		{
			ft_putstr_fd("\"", 1);
			len += 1;
			ft_putstr_fd(sorted[i] + len, 1);
			ft_putstr_fd("\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
	ft_splfree(sorted);
}

int	ft_sort_env(char **export)
{
	int		n;
	int		k;
	int		len;
	char	**sorted;

	len = ft_spllen(export);
	sorted = ft_spldup(export);
	k = len - 1;
	while (k)
	{
		n = 0;
		while (n < len - 1)
		{
			if (ft_strncmp(sorted[n], sorted[n + 1], ft_strlen(sorted[n])) > 0)
				ft_swap_ptr(&sorted[n], &sorted[n + 1]);
			n++;
		}
		k--;
	}
	ft_print_sorted(sorted);
	return (0);
}
