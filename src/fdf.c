/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 07:33:09 by eferrand          #+#    #+#             */
/*   Updated: 2017/03/14 07:03:40 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* 
** 123 = fleche gauche
** 124 = fleche droite
** 125 = fleche bas
** 126 = fleche haut
*/

int		*ft_convert(char *map, int *a)
{
	int		b;
	int		*coo;
	char	*tmp;

	tmp = map -1;
	while (*++tmp)
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

/*
** a[0] = number elems per line
** a[1] = number of lines
** b[0] = ou l on est sur la ligne du tableau
** b[1] = sur quelle ligne on est du tabeau
** xa = xabyab[0]
** xb = xabyab[1]
** ya = xabyab[2]
** yb = xabyab[3]
** pdf[0] = point de fuite sur l abscisse X
** pdf[1] = poitnde fuite sur l ordonnée Y
*/

void		writing(int *b)
{
	while (b[1]--)
		while (++b[0] < a[0])
		{
			xabyab[0] =
			pdf[0] + 10 * b[0] * 1 / coo[b[0] + (a[1] - b[1]) * a[0]];
			xabyab[2] =
			pdf[1] + 10 * b[1] * 1 / coo[b[1] + (a[1] - b[1]) * a[0]];
// equation position point avec point de fuite inclu fait au schnaps
			if (b[1])
			{
		xabyab[1] =
		pdf[0] + 10 * b[0] * 1 / coo[b[0] + (a[1] - (b[1] + 1)) * a[0]];
		xabyab[3] =
		pdf[1] + 10 * (b[1] + 1) * 1 / coo[b[1] + (a[1] - (b[1] + 1)) * a[0]];
				ft_drawline(mlx, win, xabyab);
			}
			if (b[0] < a[0])
			{
		xabyab[1] =
		pdf[0] + 10 * (b[0] + 1) * 1 / coo[(b[0] + 1) + (a[1] - b[1]) * a[0]];
		xabyab[3] =
		pdf[1] + 10 * b[1] * 1 / coo[b[1] + (a[1] - b[1]) * a[0]];
				ft_drawline(mlx, win, xabyab);
			}
		}
}

int		ft_display(int *coo, int *a)
{
	int				b[2];
	static int		pdf[2];
	int				xabyab[4];
	void			*mlx;
	void			*win;

	pdf[0] = 200;
	pdf[1] = 200;
	b[0] = -1;
	a[0] /= a[1];
	b[1] = a[1];
	if (!coo)
		return (0);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 2000, 2000, "mlx 42");
	writing();
	mlx_key_hook(win, my_key_fct, pdf);
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
	a[0] = 0;
	a[1] = 0;
//	put_tab_nbr(ft_convert(map, a), a[0], a[1]);
	if (a[0] == -1 || ((a[0] = 1) && !(ft_display(ft_convert(map, a), a))))
		ft_putstr("error read or display\n");
	return (0);
}
