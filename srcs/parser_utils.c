/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:33:31 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:33:33 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_sprites(char **map)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				k++;
			j++;
		}
		i++;
	}
	return (k);
}

void	parse_int_map(t_ptr *ptr)
{
	int		i;
	int		j;

	ptr->conf.imap = (int **)malloc(sizeof(int *) * ptr->conf.mheight);
	if (!ptr->conf.imap)
		exit_error_ptr(ptr, "Malloc error in int map");
	i = -1;
	while (++i < ptr->conf.mheight)
	{
		ptr->conf.imap[i] = (int *)malloc(sizeof(int) * ptr->conf.mwidth);
		if (!ptr->conf.imap[i])
			exit_error_ptr(ptr, "Malloc error in int map element");
	}
	i = -1;
	while (++i < ptr->conf.mheight)
	{
		j = ptr->conf.mwidth;
		while (j-- > 0)
		{
			if (ptr->conf.pmap[i][j] && ptr->conf.pmap[i][j] == '1')
				ptr->conf.imap[i][j] = 1;
			else
				ptr->conf.imap[i][j] = 0;
		}
	}
}

void	parse_map(t_ptr *ptr)
{
	int		i;
	int		j;
	int		width;

	i = 8;
	j = 0;
	width = 0;
	ptr->conf.pmap = ft_calloc((ptr->conf.msize - i) + 1, (sizeof(char *)));
	while (i < ptr->conf.msize && ptr->conf.map[i])
	{
		ptr->conf.pmap[j] = ptr->conf.map[i];
		if (ft_strlen(ptr->conf.map[i]) > width)
			width = ft_strlen(ptr->conf.map[i]);
		i++;
		j++;
	}
	ptr->conf.n_sp = count_sprites(ptr->conf.pmap);
	ptr->conf.mheight = j;
	ptr->conf.mwidth = width;
	check_map(ptr);
	parse_coordinates(ptr);
	parse_sprites(ptr);
	parse_int_map(ptr);
}

void	parse_params(t_ptr *ptr)
{
	parse_res(ptr);
	parse_tex(ptr);
	parse_col(ptr);
	parse_map(ptr);
}

int	string_is_valid(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}
