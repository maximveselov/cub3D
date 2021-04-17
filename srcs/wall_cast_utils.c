/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:34:20 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:34:33 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_dir(t_main *main, t_ptr *ptr, int x)
{
	ptr->plr.camera_x = 2 * x / (double)ptr->mlx.width - 1;
	ptr->plr.ray_x = main->dir_x + main->plane_x * ptr->plr.camera_x;
	ptr->plr.ray_y = main->dir_y + main->plane_y * ptr->plr.camera_x;
	ptr->plr.map_x = (int)main->x;
	ptr->plr.map_y = (int)main->y;
	ptr->plr.ddist_x = fabs(1 / ptr->plr.ray_x);
	ptr->plr.ddist_y = fabs(1 / ptr->plr.ray_y);
	ptr->plr.hit = 0;
}

void	calc_step(t_main *main, t_ptr *ptr)
{
	if (ptr->plr.ray_x < 0)
	{
		ptr->plr.step_x = -1;
		ptr->plr.sdist_x = (main->x - ptr->plr.map_x) * ptr->plr.ddist_x;
	}
	else
	{
		ptr->plr.step_x = 1;
		ptr->plr.sdist_x = (ptr->plr.map_x + 1.0 - main->x) * ptr->plr.ddist_x;
	}
	if (ptr->plr.ray_y < 0)
	{
		ptr->plr.step_y = -1;
		ptr->plr.sdist_y = (main->y - ptr->plr.map_y) * ptr->plr.ddist_y;
	}
	else
	{
		ptr->plr.step_y = 1;
		ptr->plr.sdist_y = (ptr->plr.map_y + 1.0 - main->y) * ptr->plr.ddist_y;
	}
}

void	dda(t_main *main, t_ptr *ptr)
{
	while (ptr->plr.hit == 0)
	{
		if (ptr->plr.sdist_x < ptr->plr.sdist_y)
		{
			ptr->plr.sdist_x += ptr->plr.ddist_x;
			ptr->plr.map_x += ptr->plr.step_x;
			ptr->plr.side = 0;
		}
		else
		{
			ptr->plr.sdist_y += ptr->plr.ddist_y;
			ptr->plr.map_y += ptr->plr.step_y;
			ptr->plr.side = 1;
		}
		if (main->map[ptr->plr.map_x][ptr->plr.map_y] > 0)
			ptr->plr.hit = 1;
	}
}

void	calc_drawline(t_main *main, t_ptr *ptr)
{
	if (ptr->plr.side == 0)
	{
		ptr->plr.pwdist = (ptr->plr.map_x - main->x + (1 - ptr->plr.step_x)
				/ 2) / ptr->plr.ray_x;
	}
	else
		ptr->plr.pwdist = (ptr->plr.map_y - main->y + (1 - ptr->plr.step_y) / 2)
			/ ptr->plr.ray_y;
	ptr->mlx.lheight = (int)(ptr->mlx.height / ptr->plr.pwdist);
	ptr->mlx.dstart = -ptr->mlx.lheight / 2 + ptr->mlx.height / 2;
	if (ptr->mlx.dstart < 0)
		ptr->mlx.dstart = 0;
	ptr->mlx.dend = ptr->mlx.lheight / 2 + ptr->mlx.height / 2;
	if (ptr->mlx.dend >= ptr->mlx.height)
		ptr->mlx.dend = ptr->mlx.height - 1;
}
