/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:32:23 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:32:24 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite_arr(t_main *main, t_ptr *ptr)
{
	int		i;

	i = 0;
	(*main).sprord = malloc(sizeof(int) * (*ptr).conf.n_sp);
	if (!(*main).sprord)
		exit_error_main(main, "Sprite array malloc error");
	while (i < (*ptr).conf.n_sp)
	{
		(*main).sprord[i] = 0;
		i++;
	}
	(*main).sprdist = malloc(sizeof(double) * (*ptr).conf.n_sp);
	if (!(*main).sprdist)
		exit_error_main(main, "Sprite array malloc error");
	i = 0;
	while (i < (*ptr).conf.n_sp)
	{
		(*main).sprdist[i] = 0.0;
		i++;
	}
}

void	init_buf(t_main *main, t_ptr *ptr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	(*main).buf = (int **)malloc(sizeof(int *) * (*ptr).mlx.height);
	if (!(*main).buf)
		exit_error_main(main, "Malloc buf error");
	while (i < (*ptr).mlx.height)
	{
		(*main).buf[i] = (int *)malloc(sizeof(int) * (*ptr).mlx.width);
		if (!(*main).buf[i])
			exit_error_main(main, "Malloc buf element error");
		i++;
	}
	i = -1;
	while (++i < (*ptr).mlx.height)
	{
		j = -1;
		while (++j < (*ptr).mlx.width)
			(*main).buf[i][j] = 0;
	}
}

void	init_tex_buf(t_main *main, t_ptr *ptr)
{
	int			i;
	int			j;

	i = -1;
	(*main).buf_z = (double *)malloc(sizeof(double) * (*ptr).mlx.width);
	if (!(*main).buf_z)
		exit_error_main(main, "Zbuf malloc error");
	(*main).texture = (int **)malloc(sizeof(int *) * 11);
	if (!(*main).texture)
		exit_error_main(main, "Texture malloc error");
	while (++i < 11)
	{
		(*main).texture[i] = (int *)malloc(sizeof(int) * (TEX_H * TEX_W));
		if (!(*main).texture[i])
			exit_error_main(main, "Texture element malloc error");
	}
	i = -1;
	while (++i < 11)
	{
		j = -1;
		while (++j < TEX_H * TEX_W)
			(*main).texture[i][j] = 0;
	}
}

void	init_structs(char *argv, t_main *main, t_ptr *ptr)
{
	(*ptr) = init_ptr();
	parse_conf(ptr, argv);
	(*main).map = (*ptr).conf.imap;
	init_sprite_arr(main, ptr);
	(*main).mlx = mlx_init();
	(*main).x = (*ptr).plr.x;
	(*main).y = (*ptr).plr.y;
	get_right_dir(main, (*ptr).conf.dir);
	(*main).a = 0;
	(*main).w = 0;
	(*main).s = 0;
	(*main).d = 0;
	(*main).esc = 0;
	(*ptr).mlx = init_mlx(ptr);
	(*main).ptr = (*ptr);
	(*main).mspeed = 0.05;
	(*main).rspeed = 0.05;
	init_buf(main, ptr);
	init_tex_buf(main, ptr);
	load_texture(main, ptr);
}
