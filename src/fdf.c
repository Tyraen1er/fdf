/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 01:38:18 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/29 04:15:09 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	all[0] = mlx;
**	all[1] = win;
**	all[2] = line;
*/

int		ft_display(t_line *line)
{
	void	*all[3];

	if (!line)
		return (0);
	zminmax(line);
	if (!(all[0] = mlx_init()) ||
			!(all[1] = mlx_new_window(all[0], 1800, 1800, "mlx 42")))
		exit(3);
	line = ft_whichline(1);
	while (line->next)
		line = line->next;
	writing(all, line, 1);
	mlx_key_hook(all[1], my_key_fct, all);
	mlx_loop(all[0]);
	return (1);
}

t_line	*ft_createline(int l)
{
	t_line	*new;

	if (!(new = malloc(sizeof(t_line))))
		return (NULL);
	new->sizeline = 0;
	new->line = l;
	new->vector = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_line	*ft_whichline(int l)
{
	static t_line	*begin = NULL;
	t_line			*tmp;

	if ((tmp = begin))
		while (tmp->next && tmp->line != l)
			tmp = tmp->next;
	if (!begin || tmp->line != l)
	{
		if (!begin)
			begin = ft_createline(l);
		else
		{
			tmp->next = ft_createline(l);
			tmp->next->prev = tmp;
		}
		tmp = (tmp ? tmp->next : begin);
	}
	return (tmp);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		a;
	char	buf[151];
	char	*map;
	char	*tmp;

	map = ft_memalloc(1);
	if (argc != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((a = read(fd, buf, 150)) && a != -1)
	{
		buf[a] = 0;
		tmp = ft_strjoin(map, buf);
		ft_memdel((void *)&map);
		map = tmp;
	}
	if (a == -1 || ((a = 1) && !(ft_display(ft_convert(map)))))
		ft_putstr("error read or display\n");
	return (0);
}
