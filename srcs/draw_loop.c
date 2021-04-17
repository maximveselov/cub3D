/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:31:52 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:31:54 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_main *main, t_ptr *ptr)
{
	int			i;
	int			j;

	i = 0;
	while (i < ptr->mlx.height)
	{
		j = 0;
		while (j < ptr->mlx.width)
		{
			main->img.data[i * ptr->mlx.width + j] = main->buf[i][j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(main->mlx, main->win, main->img.image, 0, 0);
}

void	calc(t_main *main, t_ptr *ptr)
{
	cast_floor(main, ptr);
	cast_walls(main, ptr);
	cast_sprites(ptr, main);
}

int	main_loop(t_main *main)
{
	t_ptr		ptr;

	ptr = main->ptr;
	calc(main, &ptr);
	draw(main, &ptr);
	update_key(main);
	return (0);
}

void	load_image(t_main *main, int *texture, char *path, t_img *img)
{
	int			i;
	int			j;

	i = 0;
	img->image = mlx_xpm_file_to_image(main->mlx, path, &img->width,
			&img->height);
	if (!img->image)
		exit_error_main(main, "Texture file corrupted");
	img->data = (int *)mlx_get_data_addr(img->image, &img->bpp,
			&img->line_length, &img->endian);
	if (!img->data)
		exit_error_main(main, "Texture file corrupted");
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			texture[img->width * i + j] = img->data[img->width * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(main->mlx, img->image);
}

void	load_texture(t_main *main, t_ptr *ptr)
{
	t_img		img;

	load_image(main, main->texture[0], ptr->conf.so, &img);
	load_image(main, main->texture[1], ptr->conf.no, &img);
	load_image(main, main->texture[2], ptr->conf.ea, &img);
	load_image(main, main->texture[3], ptr->conf.we, &img);
	load_image(main, main->texture[4], ptr->conf.sp, &img);
}
