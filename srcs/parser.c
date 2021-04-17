/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:33:18 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:33:19 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_format(char *file, char *format)
{
	int		i;

	i = ft_strlen(file) - ft_strlen(format);
	if (file[i])
	{
		if (!ft_strncmp(&file[i], format, i))
			return (1);
	}
	return (0);
}

void	conf_to_struct(t_list **head, t_ptr *ptr)
{
	char	**map;
	int		i;
	t_list	*tmp;

	tmp = *head;
	map = ft_calloc(ft_lstsize(tmp) + 1, sizeof(char *));
	i = 0;
	while (tmp)
	{
		map[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	ptr->conf.msize = i;
	ptr->conf.map = map;
	parse_params(ptr);
	clear_list(head);
}

static void	read_config(int fd, char **line, int *ret, t_list **head)
{
	while ((*ret) >= 0)
	{
		if (string_is_valid((*line)))
			ft_lstadd_back(head, ft_lstnew((*line)));
		else
			free((*line));
		if ((*ret) == 0)
			break ;
		(*ret) = get_next_line(fd, line);
	}
}

void	parse_conf(t_ptr *ptr, char *file)
{
	int		fd;
	int		ret;
	t_list	*head;
	char	*line;

	if (!check_file_format(file, ".cub")
		|| open(file, O_DIRECTORY) == 1)
		exit_error_ptr(ptr, "Invalid map file");
	fd = open(file, O_RDONLY);
	if (fd < 1)
		exit_error_ptr(ptr, "Cannot read map file");
	head = NULL;
	ret = get_next_line(fd, &line);
	read_config(fd, &line, &ret, &head);
	close(fd);
	if (ret < 0)
		exit_error_ptr(ptr, "Unable to read config file");
	conf_to_struct(&head, ptr);
}
