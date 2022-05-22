/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:43:09 by mtiesha           #+#    #+#             */
/*   Updated: 2022/05/20 17:43:34 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
