/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:34:03 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:34:04 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_main *main, t_ptr *ptr)
{
	int		stripe;
	int		tex_x;

	stripe = ptr->sprite.d_start_x;
	while (stripe < ptr->sprite.d_end_x)
	{
		tex_x = (int)((256 * (stripe - (-ptr->sprite.width / 2
							+ ptr->sprite.screen_x)) * TEX_W
					/ ptr->sprite.width) / 256);
		if (ptr->sprite.trans_y > 0 && stripe > 0 && stripe < ptr->mlx.width
			&& ptr->sprite.trans_y < main->buf_z[stripe])
			fill_sprite_buf(main, ptr, stripe, tex_x);
		stripe++;
	}
}

void	cast_sprites(t_ptr *ptr, t_main *main)
{
	int		i;

	i = 0;
	while (i < ptr->conf.n_sp)
	{
		main->sprord[i] = i;
		main->sprdist[i] = ((main->x - ptr->conf.sprites[i][0]) * (main->x
					- ptr->conf.sprites[i][0]) + (main->y
					- ptr->conf.sprites[i][1]) * (main->y
					- ptr->conf.sprites[i][1]));
		i++;
	}
	sprite_sort(main->sprord, main->sprdist, ptr->conf.n_sp);
	i = 0;
	while (i < ptr->conf.n_sp)
	{
		sprite_matrix(ptr, i, main);
		sprite_drawline(ptr);
		draw_sprite(main, ptr);
		i++;
	}
}
