/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:34:10 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:34:11 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_floor(t_main *main, const t_ptr *ptr)
{
	int			i;
	int			j;

	i = ptr->mlx.height / 2 + 1;
	while (++i < ptr->mlx.height)
	{
		j = 0;
		while (++j < ptr->mlx.width)
		{
			main->buf[i][j] = ptr->conf.floor;
			main->buf[ptr->mlx.height - i - 1][j] = ptr->conf.ceil;
		}
	}
}

int	get_right_tex(t_ptr *ptr)
{
	int			ret;

	ret = 0;
	if (ptr->plr.side == 0 && ptr->plr.ray_x > 0)
		ret = 0;
	else if (ptr->plr.side == 0 && ptr->plr.ray_x < 0)
		ret = 1;
	else if (ptr->plr.side == 1 && ptr->plr.ray_y > 0)
		ret = 2;
	else if (ptr->plr.side == 1 && ptr->plr.ray_y < 0)
		ret = 3;
	return (ret);
}

void	calc_tex(t_main *main, t_ptr *ptr)
{
	if (ptr->plr.side == 0)
		ptr->plr.wall_x = main->y + ptr->plr.pwdist * ptr->plr.ray_y;
	else
		ptr->plr.wall_x = main->x + ptr->plr.pwdist * ptr->plr.ray_x;
	ptr->plr.wall_x -= floor((ptr->plr.wall_x));
	ptr->plr.tex_x = (int)(ptr->plr.wall_x * (double)TEX_W);
	if (ptr->plr.side == 0 && ptr->plr.ray_x > 0)
		ptr->plr.tex_x = TEX_W - ptr->plr.tex_x - 1;
	if (ptr->plr.side == 1 && ptr->plr.ray_y < 0)
		ptr->plr.tex_x = TEX_W - ptr->plr.tex_x - 1;
	ptr->plr.step = 1.0 * TEX_H / ptr->mlx.lheight;
	ptr->plr.tex_pos = (ptr->mlx.dstart - ptr->mlx.height
			/ 2 + ptr->mlx.lheight / 2) * ptr->plr.step;
}

void	draw_tex_line(t_main *main, t_ptr *ptr, int x, int tex_n)
{
	int			y;
	int			tex_y;
	int			color;

	y = ptr->mlx.dstart;
	while (y < ptr->mlx.dend)
	{
		tex_y = (int)ptr->plr.tex_pos & (TEX_H - 1);
		ptr->plr.tex_pos += ptr->plr.step;
		color = main->texture[tex_n][TEX_H * tex_y + ptr->plr.tex_x];
		if (ptr->plr.side == 1)
			color = (color >> 1) & 8355711;
		main->buf[y][x] = color;
		y++;
	}
}

void	cast_walls(t_main *main, t_ptr *ptr)
{
	int			x;
	int			tex_n;

	x = 0;
	while (x < ptr->mlx.width)
	{
		calc_dir(main, ptr, x);
		calc_step(main, ptr);
		dda(main, ptr);
		calc_drawline(main, ptr);
		tex_n = get_right_tex(ptr);
		calc_tex(main, ptr);
		draw_tex_line(main, ptr, x, tex_n);
		main->buf_z[x] = ptr->plr.pwdist;
		x++;
	}
}
