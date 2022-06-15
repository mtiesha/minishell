/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:58:10 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/13 11:58:30 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_minmax(int a, int b, char *min_or_max)
{
	if ('i' == min_or_max[1])
	{
		if (a > b)
			return (b);
		return (a);
	}
	if (a < b)
		return (b);
	else if (a > b)
		return (a);
	if (a == b)
		return (0);
	return (-1);
}

int	ft_iscinstr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
