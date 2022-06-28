/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 07:04:53 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 08:25:45 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_multifree(void *m1, void *m2, void *m3)
{
	if (m1 != NULL)
	{
		free(m1);
		m1 = NULL;
	}
	if (m2 != NULL)
	{
		free(m2);
		m2 = NULL;
	}
	if (m3 != NULL)
	{
		free(m3);
		m3 = NULL;
	}
}
