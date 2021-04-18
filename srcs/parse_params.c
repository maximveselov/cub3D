/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:32:58 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:33:00 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_res(t_ptr *ptr)
{
	int		i;
	char	**res;
	char	*line;

	i = 0;
	line = NULL;
	while (i < ptr->conf.msize && ptr->conf.map[i])
	{
		if (ft_strnstr(ptr->conf.map[i], "R ", 4))
		{
			line = ptr->conf.map[i];
			break ;
		}
		i++;
	}
	if (!line)
		exit_error_ptr(ptr, "Invalid resolution config");
	res = ft_split(line, ' ');
	if (!res[1] || !res[2] || !ft_isdigit(res[1][0]) || !ft_isdigit(res[2][0]))
		exit_error_ptr(ptr, "Invalid resolution config");
	ptr->conf.s_height = ft_atoi(res[2]);
	ptr->conf.s_width = ft_atoi(res[1]);
	clear_map(res);
	if (ptr->conf.s_width <= 0 || ptr->conf.s_height <= 0)
		exit_error_ptr(ptr, "Invalid resolution config");
}

void	fill_tex(char **dest, char *src, t_ptr *ptr)
{
	char	**tmp;

	tmp = ft_split(src, ' ');
	*dest = ft_strdup(tmp[1]);
	if (!check_file_format(*dest, ".xpm"))
		exit_error_ptr(ptr, "Invalid texture file");
	clear_map(tmp);
}

void	parse_tex(t_ptr *ptr)
{
	int		i;
	char	**map;

	i = 0;
	map = ptr->conf.map;
	while (i < ptr->conf.msize && map[i])
	{
		if (ft_strnstr(map[i], "NO ", ft_strlen(map[i])))
			fill_tex(&(ptr->conf.no), map[i], ptr);
		if (ft_strnstr(map[i], "SO ", ft_strlen(map[i])))
			fill_tex(&(ptr->conf.so), map[i], ptr);
		if (ft_strnstr(map[i], "EA ", ft_strlen(map[i])))
			fill_tex(&(ptr->conf.ea), map[i], ptr);
		if (ft_strnstr(map[i], "WE ", ft_strlen(map[i])))
			fill_tex(&(ptr->conf.we), map[i], ptr);
		if (ft_strnstr(map[i], "S ", ft_strlen(map[i])))
			fill_tex(&(ptr->conf.sp), map[i], ptr);
		i++;
	}
	if (!ptr->conf.no || !ptr->conf.so || !ptr->conf.ea || !ptr->conf.we
		|| !ptr->conf.sp)
		exit_error_ptr(ptr, "Invalid texture config");
}

void	parse_rgb(char *src, int *dest, t_ptr *ptr)
{
	char	**tmp;
	char	**rgb;

	tmp = ft_split(src, ' ');
	rgb = ft_split(tmp[1], ',');
	if (rgb[0] && rgb[1] && rgb[2])
		*dest = create_trgb(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]),
				ft_atoi(rgb[2]));
	clear_map(tmp);
	if (!rgb[0] || !rgb[1] || !rgb[2] || (ft_atoi(rgb[0]) < 0
			|| ft_atoi(rgb[0]) > 255) || (ft_atoi(rgb[1]) < 0
			|| ft_atoi(rgb[1]) > 255)
		|| (ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255))
	{
		clear_map(rgb);
		exit_error_ptr(ptr, "Invalid color config");
	}
	clear_map(rgb);
}

void	parse_col(t_ptr *ptr)
{
	int		i;
	char	**map;

	i = 0;
	map = ptr->conf.map;
	while (i < ptr->conf.msize && map[i])
	{
		if (ft_strnstr(map[i], "F ", ft_strlen(map[i])))
			parse_rgb(map[i], &(ptr->conf.floor), ptr);
		if (ft_strnstr(map[i], "C ", ft_strlen(map[i])))
			parse_rgb(map[i], &(ptr->conf.ceil), ptr);
		if (ptr->conf.floor && ptr->conf.ceil)
			break ;
		i++;
	}
	if (ptr->conf.floor < 0 || ptr->conf.ceil < 0)
		exit_error_ptr(ptr, "Invalid color config");
}
