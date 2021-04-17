/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:23:29 by aannett           #+#    #+#             */
/*   Updated: 2021/03/12 15:57:59 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_nsfw(const char *s, unsigned int pos, size_t len)
{
	char			*ret;
	size_t			i;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	if (s)
	{
		while (i < len && s[i + pos] != 0)
		{
			ret[i] = s[i + pos];
			i++;
		}
	}
	ret[i] = 0;
	return (ret);
}
