/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:33:41 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:33:45 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_header(t_main *main, int file, int size)
{
	int				buf;

	write(file, "BM", 2);
	write(file, &size, 4);
	buf = 0;
	write(file, &buf, 4);
	buf = 54;
	write(file, &buf, 4);
	buf = 40;
	write(file, &buf, 4);
	write(file, &main->ptr.mlx.width, 4);
	write(file, &main->ptr.mlx.height, 4);
	buf = 1;
	write(file, &buf, 2);
	write(file, &main->img.bpp, 2);
	buf = 0;
	write(file, &buf, 24);
}

void	draw_bmp(t_main *main, int file)
{
	int				i;
	int				j;

	i = main->ptr.mlx.height;
	while (i >= 0)
	{
		j = 0;
		while (j < main->ptr.mlx.width)
		{
			write(file, &main->img.data[i * main->img.line_length / 4 + j],
				4);
			j++;
		}
		i--;
	}
}

void	screenshot(t_main *main)
{
	int				fd;
	int				size;
	int				padding;

	fd = open("screenshot.bmp", O_APPEND | O_CREAT | O_TRUNC | O_WRONLY);
	if (!fd)
		exit_error_main(main, "Unable to create screenshot");
	padding = (4 - (main->ptr.conf.s_width * 3) % 4) % 4;
	size = 54 + (3 * (main->ptr.conf.s_width + padding))
		* main->ptr.conf.s_height;
	main_loop(main);
	fill_header(main, fd, size);
	draw_bmp(main, fd);
	close(fd);
}
