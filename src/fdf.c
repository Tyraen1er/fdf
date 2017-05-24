/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 01:38:18 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/24 15:05:55 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zminmax(t_line *line)
{
	int		a;
	int		z[2];

	line = ft_whichline(1);
	z[0] = line->vector[0][4];
	z[1] = z[0];
	while (line)
	{
		a = -1;
		while (++a < line->sizeline)
		{
			if (line->vector[a][4] < z[0])
				z[0] = line->vector[a][4];
			if (z[1] < line->vector[a][4])
				z[1] = line->vector[a][4];
		}
		line = line->next;
	}
	ft_color(NULL, z, 0);
}

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

t_line		*ft_createline(int l)
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

t_line		*ft_whichline(int l)
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

/*
 ** xa
 ** xb
 ** ya
 ** yb
 ** za || color a
 ** zb || color b
 */

int			***ft_mallocwriting(t_line *line)
{
	int	***coo;
	int	a;

	coo = (int***)malloc(sizeof(int**) * line->line);
	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		coo[line->line - 1] = (int**)malloc(sizeof(int*) * line->sizeline);
		while (a < line->sizeline)
		{
			coo[line->line - 1][a] = ft_param(line->vector[a], 0, 0);
			++a;
		}
		line = line->next;
	}
	return (coo);
}

void		ft_freewriting(int ***coo, t_line *line)
{
	int	a;

	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		while (a < line->sizeline)
		{
			free(coo[line->line - 1][a]);
			++a;
		}
		free(coo[line->line - 1]);
		line = line->next;
	}
}

void		writing(void **all, t_line *line, int color)
{
	int		***coo;
	int		xabyab[7];
	int		a;

	coo = ft_mallocwriting(line);
	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		while (a < line->sizeline)
		{
			xabyab[4] = 0;
			xabyab[5] = 0;
			if (color)
				xabyab[4] = (color == 1) ? line->vector[a][4] : line->vector[a][5];
			xabyab[0] = coo[line->line - 1][a][2];
			xabyab[2] = coo[line->line - 1][a][3];
			if (line->next && a < line->next->sizeline)
			{
				xabyab[1] = coo[line->line][a][2];
				xabyab[3] = coo[line->line][a][3];
				if (color)
					xabyab[5] = (color == 1) ? line->next->vector[a][4] : line->next->vector[a][5];
				ft_drawline(all, xabyab, color);
			}
			if (a < line->sizeline - 1)
			{
				xabyab[1] = coo[line->line - 1][a + 1][2];
				xabyab[3] = coo[line->line - 1][a + 1][3];
				if (color)
					xabyab[5] = (color == 1) ? line->vector[a + 1][4] : line->vector[a + 1][5];
				ft_drawline(all, xabyab, color);
			}
			++a;
		}
		line = line->next;
	}
	ft_freewriting(coo, line);
}

t_line		*ft_convert(char *map)
{
	int		a;
	int		b;
	int		l;
	t_line	*tmp;

	a = 0;
	l = 1;
	if (!map || !*map)
		return (NULL);
	while (*map && !(ft_isdigit(*map)))
		++map;
	if (!*map)
		return (NULL);
	while (map[a])
	{
		tmp = ft_whichline(l);
		b = a;
		while (map[a] && map[a] != '\n')
		{
			if (ft_isdigit(map[a]) && ++tmp->sizeline)
				while (map[a] != ' ' && map[a] != '\t' && map[a] != '\n'
						&& map[a])
					++a;
			else
				++a;
		}
		if (map[a] == '\n' || !map[a])
		{
			if (!(tmp->vector = (int**)malloc(sizeof(int*) * tmp->sizeline)))
				return (NULL);
			a = b;
			b = 0;
			while (map[a] && map[a] != '\n')
			{
				if (ft_isdigit(map[a]) ||
						(map[a] == '-' && ft_isdigit(map[a + 1])))
				{
					tmp->vector[b] = (int*)malloc(sizeof(int) * 6);

					tmp->vector[b][0] = 1;
					tmp->vector[b][1] = 3;
					tmp->vector[b][2] = b;
					tmp->vector[b][3] = l - 1;
					tmp->vector[b][4] = ft_atoifdf(&map[a]);
					while (map[a] != ' ' && map[a] != '\t' &&
							map[a] != ',' && map[a] != '\n' && map[a])
						++a;
					tmp->vector[b][5] = ((map[a] == ',' &&
								ft_isdigit(map[a + 1])) ?
							ft_atoifdf(&map[a + 1]) : 0xFFFFFF);
					while (map[a] != ' ' && map[a] != '\t' &&
							map[a] != '\n' && map[a])
						++a;
					++b;
				}
				else
					++a;
			}
			++l;
		}
		if (map[a])
			++a;
	}
	return (tmp);
}

int			main(int argc, char **argv)
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
