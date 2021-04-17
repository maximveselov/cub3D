/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:32:34 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:32:35 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_conf	init_conf(void)
{
	t_conf		ret;

	ret.s_height = 0;
	ret.s_width = 0;
	ret.no = NULL;
	ret.so = NULL;
	ret.we = NULL;
	ret.ea = NULL;
	ret.sp = NULL;
	ret.ceil = 0;
	ret.floor = 0;
	ret.map = NULL;
	ret.pmap = NULL;
	ret.sprites = NULL;
	ret.imap = NULL;
	ret.n_sp = 0;
	return (ret);
}

static t_plr	init_plr(void)
{
	t_plr		ret;

	ret.x = 0;
	ret.y = 0;
	return (ret);
}

void	get_right_res(t_mlx *mlx)
{
	int			height;
	int			width;

	width = 320;
	height = 240;
	while (width < mlx->width && height < mlx->height)
	{
		width += 320;
		height += 240;
	}
	mlx->width = width;
	mlx->height = height;
}

t_mlx	init_mlx(t_ptr *ptr)
{
	t_mlx		ret;

	if (!ptr)
		exit_error_ptr(ptr, "something went wrong...");
	ret.ptr = mlx_init();
	mlx_get_screen_size(ret.ptr, &(ret.width), &(ret.height));
	if (ptr->conf.s_width < ret.width)
		ret.width = ptr->conf.s_width;
	if (ptr->conf.s_height < ret.height)
		ret.height = ptr->conf.s_height;
	get_right_res(&ret);
	ret.lheight = 0;
	ret.dstart = 0;
	ret.dend = 0;
	ret.buf = NULL;
	ret.tex = NULL;
	ret.buf_z = NULL;
	ret.sprord = NULL;
	ret.sprdist = NULL;
	return (ret);
}

t_ptr	init_ptr(void)
{
	t_ptr		ret;

	ret.conf = init_conf();
	ret.plr = init_plr();
	return (ret);
}
