/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:19:25 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/07 21:06:11 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_chardel(char **str, int index)
{
	char	*ret;
	char	*ptr;

	ret = NULL;
	ptr = (*str);
	ret = (char *)ft_calloc(ft_strlen(ptr), sizeof(char));
	ret = (char *)ft_memcpy(ret, ptr, index);
	printf("ret:%s+\n", ret);
	while (ptr[++index])
		ret[index - 1] = ptr[index];
	printf("ret+all:%s+\n", ret);
	free(ptr);
	return (ret);
}

char	*ft_charadd(char **str, int index, char c)
{
	char	*ret;
	char	*ptr;

	ret = NULL;
	ptr = (*str);
	ret = (char *)ft_calloc(2 + ft_strlen(ptr), sizeof(char));
	ret = (char *)ft_memcpy(ret, ptr, index);
	printf("ret:%s+\n", ret);
	ret[index] = c;
	printf("ret+c:%s+\n", ret);
	while (ptr[index])
	{
		ret[index + 1] = ptr[index];
		index++;
	}
	printf("ret+all:%s+\n", ret);
	free(ptr);
	return (ret);
}
