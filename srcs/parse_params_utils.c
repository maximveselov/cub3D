/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:33:09 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:33:10 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_plr_info(t_ptr *ptr, int x, int y, char dir)
{
	ptr->plr.x = (float)x + 0.5;
	ptr->plr.y = (float)y + 0.5;
	ptr->conf.dir = dir;
}

void	parse_coordinates(t_ptr *ptr)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = ptr->conf.pmap;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == 'N' || tmp[i][j] == 'S'
				|| tmp[i][j] == 'W' || tmp[i][j] == 'E')
			{
				if (ptr->plr.x || ptr->plr.y)
					exit_error_ptr(ptr, "Too many starting points");
				else
					get_plr_info(ptr, i, j, tmp[i][j]);
			}
			j++;
		}
		i++;
	}
}

double	*get_sprite_array(int x, int y)
{
	double	*ret;

	ret = malloc(sizeof(double) * 2);
	if (!ret)
		return (NULL);
	ret[0] = x + 0.5;
	ret[1] = y + 0.5;
	return (ret);
}

void	parse_sprites(t_ptr *ptr)
{
	double	**sprite;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	sprite = ft_calloc(ptr->conf.n_sp + 1, sizeof(int *));
	while (ptr->conf.pmap[i])
	{
		j = 0;
		while (ptr->conf.pmap[i][j])
		{
			if (ptr->conf.pmap[i][j] == '2')
			{
				sprite[k] = get_sprite_array(i, j);
				if (!sprite[k])
					exit_error_ptr(ptr, "Sprite buf malloc problem\n");
				k++;
			}
			j++;
		}
		i++;
	}
	ptr->conf.sprites = sprite;
}
