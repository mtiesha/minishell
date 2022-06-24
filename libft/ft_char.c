/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:19:25 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/24 12:39:55 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chardel(char **str, int index)
{
	char	*ret;
	char	*ptr;

	ret = NULL;
	ptr = (*str);
	ret = (char *)ft_calloc(ft_strlen(ptr), sizeof(char));
	ret = (char *)ft_memcpy(ret, ptr, index);
	while (ptr[++index])
		ret[index - 1] = ptr[index];
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
	ret[index] = c;
	while (ptr[index])
	{
		ret[index + 1] = ptr[index];
		index++;
	}
	free(ptr);
	return (ret);
}

size_t	ft_count_char(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (c == str[i])
			count++;
		i++;
	}
	return (count);
}
