/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:32:03 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:32:05 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_main(t_main *main)
{
	if (main->buf)
		free_arr_int(main->buf, main->ptr.mlx.height);
	if (main->buf_z)
		free(main->buf_z);
	if (main->texture)
		free_arr_int(main->texture, 11);
	if (main->sprord)
		free(main->sprord);
	if (main->sprdist)
		free(main->sprdist);
	mlx_destroy_image(main->mlx, main->img.image);
	mlx_destroy_window(main->mlx, main->win);
}

int	exit_normal(t_main *main)
{
	free_ptr(&main->ptr);
	free_main(main);
	exit(0);
	return (0);
}

void	exit_error_ptr(t_ptr *ptr, char *error)
{
	free_ptr(ptr);
	printf("Error\n%s\nSystem error:\n%s\n", error, strerror(errno));
	exit(0);
}

void	exit_error_main(t_main *main, char *error)
{
	free_ptr(&main->ptr);
	free_main(main);
	printf("Error\n%s\nSystem error:\n%s\n", error, strerror(errno));
	exit(0);
}
