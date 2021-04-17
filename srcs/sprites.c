/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:33:55 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:33:56 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_order(t_pair *ords, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (ords[j].first > ords[j + 1].first)
			{
				tmp.first = ords[j].first;
				tmp.second = ords[j].second;
				ords[j].first = ords[j + 1].first;
				ords[j].second = ords[j + 1].second;
				ords[j + 1].first = tmp.first;
				ords[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sprite_sort(int *ord, double *dist, int n)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	sprites = (t_pair *)malloc(sizeof(t_pair) * n);
	while (i < n)
	{
		sprites[i].first = dist[i];
		sprites[i].second = ord[i];
		i++;
	}
	sort_order(sprites, n);
	i = 0;
	while (i < n)
	{
		dist[i] = sprites[n - i - 1].first;
		ord[i] = sprites[n - i - 1].second;
		i++;
	}
	free(sprites);
}

void	sprite_matrix(t_ptr *ptr, int i, t_main *main)
{
	ptr->sprite.x = ptr->conf.sprites[main->sprord[i]][0] - main->x;
	ptr->sprite.y = ptr->conf.sprites[main->sprord[i]][1] - main->y;
	ptr->sprite.inv_det = 1.0 / (main->plane_x * main->dir_y - main->dir_x
			* main->plane_y);
	ptr->sprite.trans_x = ptr->sprite.inv_det * (main->dir_y * ptr->sprite.x
			- main->dir_x * ptr->sprite.y);
	ptr->sprite.trans_y = ptr->sprite.inv_det * (-main->plane_y
			* ptr->sprite.x + main->plane_x * ptr->sprite.y);
	ptr->sprite.screen_x = (int)((ptr->mlx.width / 2) * (1 + ptr->sprite.trans_x
				/ ptr->sprite.trans_y));
	ptr->sprite.v_move_screen = (int)(VMOVE / ptr->sprite.trans_y);
	ptr->sprite.height = (int)fabs((ptr->mlx.height / ptr->sprite.trans_y)
			/ VDIV);
	ptr->sprite.d_start_y = -ptr->sprite.height / 2 + ptr->mlx.height / 2
		+ ptr->sprite.v_move_screen;
}

void	sprite_drawline(t_ptr *ptr)
{
	if (ptr->sprite.d_start_y < 0)
		ptr->sprite.d_start_y = 0;
	ptr->sprite.d_end_y = ptr->sprite.height / 2 + ptr->mlx.height / 2
		+ ptr->sprite.v_move_screen;
	if (ptr->sprite.d_end_y >= ptr->mlx.height)
		ptr->sprite.d_end_y = ptr->mlx.height - 1;
	ptr->sprite.width = (int)fabs((ptr->mlx.height / ptr->sprite.trans_y)
			/ UDIV);
	ptr->sprite.d_start_x = -ptr->sprite.width / 2 + ptr->sprite.screen_x;
	if (ptr->sprite.d_start_x < 0)
		ptr->sprite.d_start_x = 0;
	ptr->sprite.d_end_x = ptr->sprite.width / 2 + ptr->sprite.screen_x;
	if (ptr->sprite.d_end_x >= ptr->mlx.width)
		ptr->sprite.d_end_x = ptr->mlx.width - 1;
}

void	fill_sprite_buf(t_main *main, t_ptr *ptr, int stripe, int tex_x)
{
	int		i;
	int		j;
	int		color;
	int		tex_y;

	i = ptr->sprite.d_start_y;
	while (i < ptr->sprite.d_end_y)
	{
		j = (i - ptr->sprite.v_move_screen) * 256 - ptr->mlx.height
			* 128 + ptr->sprite.height * 128;
		tex_y = ((j * TEX_H) / ptr->sprite.height) / 256;
		color = main->texture[4][TEX_W * tex_y + tex_x];
		if ((color & 0x00FFFFFF) != 0)
			main->buf[i][stripe] = color;
		i++;
	}
}
