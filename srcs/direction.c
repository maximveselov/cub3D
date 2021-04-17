/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:31:41 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:31:45 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dir_utils(t_main *main, char c)
{
	if (c == 'N')
	{
		main->dir_y = 0.0;
		main->dir_x = -1.0;
		main->plane_x = 0.0;
		main->plane_y = -0.66;
	}
	else if (c == 'W')
	{
		main->dir_y = 0.0;
		main->dir_x = 1.0;
		main->plane_x = 0.0;
		main->plane_y = 0.66;
	}
}

void	get_right_dir(t_main *main, char c)
{
	if (c == 'S')
	{
		main->dir_y = -1.0;
		main->dir_x = 0.0;
		main->plane_x = 0.66;
		main->plane_y = 0.0;
	}
	else if (c == 'E')
	{
		main->dir_y = 1.0;
		main->dir_x = 0.0;
		main->plane_x = -0.66;
		main->plane_y = 0.0;
	}
	else
		dir_utils(main, c);
}
