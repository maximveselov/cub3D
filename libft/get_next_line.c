/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:40:00 by aannett           #+#    #+#             */
/*   Updated: 2021/03/05 17:21:20 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*ft_realloc_buff(t_gnl *list,
size_t pos, size_t len)
{
	char					*tmp;

	if (list->l_buff)
	{
		tmp = ft_substr_nsfw(list->l_buff, pos, len);
		if (!tmp)
			return (NULL);
		ft_bzero(list->l_buff, list->b_size);
		free(list->l_buff);
	}
	else
	{
		tmp = malloc(sizeof(char) * len + 1);
		if (!tmp)
			return (NULL);
		ft_bzero(tmp, len);
	}
	list->l_buff = tmp;
	list->b_size = len;
	return (list);
}

static t_gnl	*ft_lstbuild_fd(t_gnl *list, int fd)
{
	if (!ft_realloc_buff(list, 0, 1024))
		return (NULL);
	list->b_read = 0;
	list->b_written = 0;
	list->filedes = fd;
	list->b_size = 1024;
	return (list);
}

static int	ft_save_newline(char **line, t_gnl *lst)
{
	char					*ptr;
	char					*tmp;
	size_t					j;

	*line = NULL;
	tmp = NULL;
	ptr = ft_memchr(lst->l_buff, '\n', lst->b_read);
	if (ptr)
		j = (size_t)(ptr - ((char *)lst->l_buff + lst->b_written));
	else
		j = lst->b_read - lst->b_written;
	*line = ft_substr_nsfw(lst->l_buff, 0, j);
	if (!*line)
		return (-1);
	if (ptr)
		lst->b_written = j + 1;
	else
		lst->b_written = j;
	if (ptr)
		tmp = ft_substr_nsfw(lst->l_buff, j + 1, lst->b_read - (j + 1));
	save_new_line_util(lst, j);
	lst->l_buff = tmp;
	if (!ptr)
		return (0);
	return (1);
}

static int	ft_read_buff(t_gnl *list)
{
	ssize_t					ret;

	list->s_buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!list->s_buff)
		return (-1);
	ft_bzero(list->s_buff, BUFFER_SIZE + 1);
	ret = read(list->filedes, list->s_buff, BUFFER_SIZE);
	while (ret)
	{
		if ((list->b_size - list->b_read) < BUFFER_SIZE)
			ft_realloc_buff(list, 0, list->b_size + BUFFER_SIZE + 1024);
		ft_memcpy(list->l_buff + list->b_read, list->s_buff, ret);
		list->b_read += ret;
		if (ft_memchr(list->s_buff, '\n', ret))
			break ;
		ft_bzero(list->s_buff, ret);
		ret = read(list->filedes, list->s_buff, BUFFER_SIZE);
	}
	free(list->s_buff);
	ft_realloc_buff(list, 0, list->b_read);
	if (ret < 0 || !list->l_buff)
		return (-1);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl			node;
	int						rvalue;

	rvalue = 1;
	if (node.filedes != fd)
		ft_lstbuild_fd(&node, fd);
	if (fd < 0 || read(fd, node.l_buff, 0) < 0
		|| BUFFER_SIZE < 1 || !line)
		return (-1);
	if ((!ft_memchr((&node)->l_buff, '\n', node.b_size)
			&& (rvalue = ft_read_buff(&node)) < 0)
		|| (rvalue = ft_save_newline(line, &node)) <= 0)
	{
		node.filedes = -1;
		return (rvalue);
	}
	return (rvalue);
}
