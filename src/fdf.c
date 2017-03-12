/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 07:33:09 by eferrand          #+#    #+#             */
/*   Updated: 2017/03/11 08:03:43 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <math.h>

int		my_key_fct(int keycode, void *param)
{
	if (keycode == 53)
		exit(3);
	printf("il se passe quelquechose\n%d\n", keycode);
	param = NULL;
	return (0);
}

int		*ft_convert(char *map, int *a)
{
	int		b;
	int		*coo;
	char	*tmp;

	tmp = map - 1;
	while (*tmp && ++tmp)
		if (*tmp == '\t' || *tmp == ' ' || (*tmp == '\n' && ++a[1]))
			++a[0];
	coo = (int*)malloc(sizeof(int) * a[0]);
	b = 0;
	while (*map)
	{
		if (*map != ' ' && *map != '\t' && *map != '\n' &&
				*map != '+' && *map != '-' && !ft_isdigit(*map))
			return (NULL);
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		if (*map)
			coo[b++] = ft_atoi(map);
		map = (*map == '+' || *map == '-') ? map + 1 : map;
		while (ft_isdigit(*map))
			++map;
	}
	return (coo);
}

/*
** xa = xabyab[0]
** xb = xabyab[1]
** ya = xabyab[2]
** yb = xabyab[3]
*/

void	ft_drawline(void *mlx, void *win, int *xabyab)
{
	int		xav;
	int		yav;
	int		x;
	int		y;

	x = xabyab[0];
	y = xabyab[2];
	xav = (xabyab[0] < xabyab[1]) ? 1 : -1;
	yav = (xabyab[2] < xabyab[3]) ? 1 : -1;
	if (xabyab[0] == xabyab[1])
		while (y != xabyab[3])
		{
			mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
			y += yav;
		}
	else
		while ((xav == 1 && x < xabyab[1]) || (xav == -1 && x > xabyab[1]))
		{
			if (abs(((xabyab[1] - xabyab[0]) * x) / (xabyab[3] - xabyab[2])))
				y += yav;
			mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
			x += xav;
		}
}

/*
** a[0] = number elem per line
*/

int		ft_display(int *coo, int *a)
{
	int		c;
	int		*xabyab;
	void	*mlx;
	void	*win;

	c = -1;
	a[0] /= a[1];
	if (!coo)
		return (0);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 2000, 2000, "mlx 42");
	mlx_key_hook(win, my_key_fct, 0);
	while (++c < a[0] &&)
	{
		ft_drawline(mlx, win, xabyab);
	}
	mlx_loop(mlx);
	return (1);
}

/*
** a[0] = return read
*/

int		main(int argc, char **argv)
{
	int		fd;
	int		a[2];
	char	buf[151];
	char	*map;
	char	*tmp;

	map = ft_memalloc(1);
	if ((a[1] = 1) && argc != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((a[0] = read(fd, buf, 150)) && a[0] != -1)
	{
		buf[a[0]] = 0;
		tmp = ft_strjoin(map, buf);
		ft_memdel((void *)&map);
		map = tmp;
	}
	if (a[0] == -1 || ((a[0] = 1) && !(ft_display(ft_convert(map, a), a))))
		ft_putstr("error read or display\n");
	return (0);
}
