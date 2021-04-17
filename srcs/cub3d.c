/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:31:18 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:31:19 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_main	main;
	t_ptr	ptr;

	if (argc < 2 || argc > 3)
		exit_error_ptr(&ptr, "Invalid arguments");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 8))
		exit_error_ptr(&ptr, "Invalid arguments");
	init_structs(argv[1], &main, &ptr);
	main.win = mlx_new_window(main.mlx, ptr.mlx.width, ptr.mlx.height,
			"mlx");
	main.img.image = mlx_new_image(main.mlx, ptr.mlx.width, ptr.mlx.height);
	main.img.data = (int *)mlx_get_data_addr(main.img.image, &main.img.bpp,
			&main.img.line_length, &main.img.endian);
	mlx_loop_hook(main.mlx, &main_loop, &main);
	if (argc == 3)
	{
		screenshot(&main);
		return (0);
	}
	mlx_hook(main.win, KEYPRESS, 0, &key_press, &main);
	mlx_hook(main.win, KEYRELEASE, 0, &key_release, &main);
	mlx_hook(main.win, KEYEXIT, 0, &exit_normal, &main);
	mlx_loop(main.mlx);
}
