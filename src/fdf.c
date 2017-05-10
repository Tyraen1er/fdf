/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 01:38:18 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/10 06:50:23 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_display(t_line *line)
{
	void	*mlx;
	void	*win;
	void	*all[3];

	if (!line)
		return (0);
	mlx = mlx_init();
	if (!mlx)
		exit(3);
	win = mlx_new_window(mlx, 1800, 1800, "mlx 42");
	if (!win)
		exit(3);
	line = ft_whichline(1);
	while (line->next)
		line = line->next;
	all[0] = mlx;
	all[1] = win;
	all[2] = line;
	writing(mlx, win, line);
	mlx_key_hook(win, my_key_fct, all);
	mlx_loop(mlx);
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
	new->next = NULL;;
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

void		writing(void *mlx, void *win, t_line *line)
{
	int		***coo;
	int		xabyab[5];
	int		a;

	xabyab[4] = 0xFFFFFF;
	coo = (int***)malloc(sizeof(int**) * line->line);
	line = ft_whichline(1);
	while (line)
	{
		coo[line->line - 1] = (int**)malloc(sizeof(int*) * line->sizeline);
		a = 0;
		while (a < line->sizeline)
		{
			coo[line->line - 1][a] = ft_param(line->vector[a], 0, 0);
			++a;
		}
		line = line->next;
	}
	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		while (a < line->sizeline)
		{
			xabyab[0] = coo[line->line - 1][a][2];
			xabyab[2] = coo[line->line - 1][a][3];
			if (line->next && a < line->next->sizeline)
			{
				xabyab[1] = coo[line->line][a][2];
				xabyab[3] = coo[line->line][a][3];
				ft_drawline(mlx, win, xabyab);
			}
			if (a < line->sizeline - 1)
			{
				xabyab[1] = coo[line->line - 1][a + 1][2];
				xabyab[3] = coo[line->line - 1][a + 1][3];
				ft_drawline(mlx, win, xabyab);
			}
			++a;
		}
		line = line->next;
	}
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

int  main(int argc, char **argv)
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
