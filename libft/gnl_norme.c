/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_norme.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:28:11 by aannett           #+#    #+#             */
/*   Updated: 2021/04/17 22:28:12 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	save_new_line_util(t_gnl *lst, size_t j)
{
	ft_bzero(lst->l_buff, lst->b_size);
	lst->b_size = lst->b_read - (j + 1);
	lst->b_read -= j + 1;
	lst->b_written = 0;
	free(lst->l_buff);
}
