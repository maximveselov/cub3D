/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:32:13 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:32:15 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_list(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		free(tmp);
		tmp = tmp->next;
	}
}

void	clear_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_arr_double(double **arr, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
}

void	free_arr_int(int **arr, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
}

void	free_ptr(t_ptr *ptr)
{
	if (ptr->conf.no)
	{
		free(ptr->conf.no);
		ptr->conf.no = NULL;
	}
	if (ptr->conf.so)
		free(ptr->conf.so);
	if (ptr->conf.ea)
		free(ptr->conf.ea);
	if (ptr->conf.we)
		free(ptr->conf.we);
	if (ptr->conf.sp)
		free(ptr->conf.sp);
	if (ptr->conf.pmap)
		free(ptr->conf.pmap);
	if (ptr->conf.map)
		clear_map(ptr->conf.map);
	if (ptr->conf.sprites)
		free_arr_double(ptr->conf.sprites, ptr->conf.n_sp + 1);
	if (ptr->conf.imap)
		free_arr_int(ptr->conf.imap, ptr->conf.mheight);
}
