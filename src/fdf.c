/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 07:33:09 by eferrand          #+#    #+#             */
/*   Updated: 2017/03/11 01:40:37 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <math.h>

// mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
/*
int		coefd(int xa, int ya, int xb, yb)
{
	(xb - xa) / (yb - ya)
}
*/

int		my_key_fct(int keycode, void *param)
{
	if (keycode == 53)
		exit(3);
	printf("il se passe quelquechose\n%d\n", keycode);
	param = NULL;
	return (0);
}

int		*ft_convert(char *map, int a)
{
	int		*coo;
	char	*tmp;

	printf("B\n");
	tmp = map;
	while (*tmp)
	{
		if (*tmp == '\t' || *tmp == ' ' || *tmp == '\n')
			++a;
		++tmp;
	}
	coo = (int*)malloc(sizeof(int) * a);
	a = 0;
	while (*map)
	{
		if (*map != ' ' && *map != '\t' && *map != '\n' &&
				*map != '+' && *map != '-' && !ft_isdigit(*map))
			return (NULL);
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		if (*map)
			coo[a++] = ft_atoi(map);
		map = (*map == '+' || *map == '-') ? map + 1 : map;
		while (ft_isdigit(*map))
			++map;
	}
	printf("C\n");
	return (coo);
}

/*
int		ft_drawline(int xa, int xb, int ya, int yb)
{
	int		f;
	int		xav;
	int		yav;
	int		x;
	int		y;

	x = xa;
	y = ya;
	xav = (xa < xb) ? 1 : -1;
	yav = (ya < yb) ? 1 : -1;
	if (xb == xa)
	{
		f = xb;
		xb = yb;
		yb = xb;
		f = xa;
		xa = ya;
		ya = f;
	}
	f = (xb - xa) / (yb - ya);
	while ((xav == 1 && x < xb) || (xav == -1 && x > xb))
	{
		if (fabs(((xb - xa) * x) / (yb - ya)))
			y += yav;
		mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
		x += xav;
	}
	return (0);
}
*/

int		ft_display(int *coo)
{
	void	*mlx;
	void	*win;
	
	printf("E\n");
	if (!coo)
		return (0);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 2000, 2000, "mlx 42");
	mlx_key_hook(win, my_key_fct, 0);
//	if (-1 == (ft_draw(int *coo)))
	mlx_loop(mlx);
	printf("F\n");
	return (1);
}

int main(int argc, char **argv)
{
	int		fd;
	int		a;
	char	buf[151];
	char	*map;
	char	*tmp;

	map = "";
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
	printf("A\n");
	if (a == -1 || !(ft_display(ft_convert(map, a))))
		return (0);
	return (0);
}
