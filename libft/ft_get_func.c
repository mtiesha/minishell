/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:56:14 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/07 12:33:48 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
*	ft_get_strnspl - find str in arrays an array, to full search put \0 to last arg
*/

char	*ft_get_strnspl(char **spl, char *str, char c)
{
	int	i;

	i = 0;
	while (spl[i])
	{
		if (!ft_memcmp(spl[i], str, ft_strnlen(spl[i], c)))
			return (spl[i]);
		i++;
	}
	return (NULL);
}
