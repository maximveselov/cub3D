/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:32:40 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:32:44 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_keys_utils(t_main *main, double old_dir_x,
double old_plane_x)
{
	if (main->a)
	{
		main->dir_x = main->dir_x * cos(-main->rspeed) - main->dir_y
			* sin(-main->rspeed);
		main->dir_y = old_dir_x * sin(-main->rspeed) + main->dir_y
			* cos(-main->rspeed);
		main->plane_x = main->plane_x * cos(-main->rspeed) - main->plane_y
			* sin(-main->rspeed);
		main->plane_y = old_plane_x * sin(-main->rspeed) + main->plane_y
			* cos(-main->rspeed);
	}
	if (main->d)
	{
		main->dir_x = main->dir_x * cos(main->rspeed) - main->dir_y
			* sin(main->rspeed);
		main->dir_y = old_dir_x * sin(main->rspeed) + main->dir_y
			* cos(main->rspeed);
		main->plane_x = main->plane_x * cos(main->rspeed) - main->plane_y
			* sin(main->rspeed);
		main->plane_y = old_plane_x * sin(main->rspeed) + main->plane_y
			* cos(main->rspeed);
	}
}

void	rotate_keys(t_main *main)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = main->dir_x;
	old_plane_x = main->plane_x;
	rotate_keys_utils(main, old_dir_x, old_plane_x);
}

void	update_key(t_main *main)
{
	if (main->w)
	{
		if (!main->map[(int)(main->x + main->dir_x * main->mspeed)]
		[(int)(main->y)])
			main->x += main->dir_x * main->mspeed;
		if (!main->map[(int)(main->x)][(int)(main->y + main->dir_y
		* main->mspeed)])
			main->y += main->dir_y * main->mspeed;
	}
	if (main->s)
	{
		if (!main->map[(int)(main->x - main->dir_x * main->mspeed)]
		[(int)(main->y)])
			main->x -= main->dir_x * main->mspeed;
		if (!main->map[(int)(main->x)][(int)(main->y - main->dir_y
		* main->mspeed)])
			main->y -= main->dir_y * main->mspeed;
	}
	rotate_keys(main);
	if (main->esc)
		exit(0);
}

int	key_press(int key, t_main *main)
{
	if (key == ESC)
		exit_normal(main);
	else if (key == W)
		main->w = 1;
	else if (key == A)
		main->a = 1;
	else if (key == S)
		main->s = 1;
	else if (key == D)
		main->d = 1;
	return (0);
}

int	key_release(int key, t_main *main)
{
	if (key == ESC)
		exit_normal(main);
	else if (key == W)
		main->w = 0;
	else if (key == A)
		main->a = 0;
	else if (key == S)
		main->s = 0;
	else if (key == D)
		main->d = 0;
	return (0);
}
