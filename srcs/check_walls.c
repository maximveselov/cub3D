/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:38:24 by aannett           #+#    #+#             */
/*   Updated: 2021/04/18 20:38:27 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall_closure(t_ptr *ptr)
{
	int	i;
	int	j;

	i = 0;
	while (ptr->conf.pmap[i])
	{
		j = 0;
		while (ptr->conf.pmap[i][j])
		{
			if ((ptr->conf.pmap[i][j] == '0' || ptr->conf.pmap[i][j] == '2'
				 || ft_strchr("NSWE", ptr->conf.pmap[i][j]))
				&& (!ptr->conf.pmap[i - 1][j] || !ptr->conf.pmap[i + 1][j]
					|| !ptr->conf.pmap[i][j - 1] || !ptr->conf.pmap[i][j + 1]))
				exit_error_ptr(ptr, "Map is not closed");
			j++;
		}
		i++;
	}
}

void	check_borders(t_ptr *ptr)
{
	int	i;
	int	j;

	i = 0;
	while (ptr->conf.pmap[i])
	{
		j = 0;
		while (ptr->conf.pmap[i][j])
		{
			if ((ptr->conf.pmap[i][j] == '0' || ptr->conf.pmap[i][j] == '2'
				 || ft_strchr("NSWE", ptr->conf.pmap[i][j]))
				&& ((ptr->conf.pmap[i - 1][j]
				&& ptr->conf.pmap[i - 1][j] == ' ')
				|| (ptr->conf.pmap[i + 1][j] && ptr->conf.pmap[i + 1][j] == ' ')
				|| (ptr->conf.pmap[i][j - 1] && ptr->conf.pmap[i][j - 1] == ' ')
				|| (ptr->conf.pmap[i][j + 1]
				&& ptr->conf.pmap[i][j + 1] == ' ')))
				exit_error_ptr(ptr, "Map is not closed");
			j++;
		}
		i++;
	}
	check_wall_closure(ptr);
}

void	check_map(t_ptr *ptr)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ptr->conf.pmap;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if ((tmp[i][j] != '1' && tmp[i][j] != '0' && tmp[i][j] != 'N'
				 && tmp[i][j] != ' ' && tmp[i][j] != 'W' && tmp[i][j] != 'E'
				 && tmp[i][j] != 'S' && tmp[i][j] != '2'))
				exit_error_ptr(ptr, "Invalid map config");
			j++;
		}
		i++;
	}
	check_borders(ptr);
}
