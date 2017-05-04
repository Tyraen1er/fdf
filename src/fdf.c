/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 07:33:09 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/04 03:57:51 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* 
** 123 = fleche gauche
** 124 = fleche droite
** 125 = fleche bas
** 126 = fleche haut
*/

int     **ft_convert(char *map, int *a)
{
	int		c;
	int		b;
	int		d;
	int		**coo;

	b = 0;
	c = 0;
	d = 0;
	while(map[c] != '\n' && map[c])
		++c;
	while (map[b])
	{
		while (map[b] == ' ' || map[b] == '\t' || map[b] == ',' ||
				(map[b] == '\n' && ++a[1]))
		{
			if (map[b] == '\n' && d != c)
			{
				printf("map = %d\n", d);
				return (NULL);
			}
			++b;
		}
		if (map[b] == '+' || map[b] == '-')
			++b;
		if ((ft_isdigit(map[b]) && ++a[0] && ++d) || !map[b])
			while (ft_isdigit(map[b]))
				++b;
		else
		{
			printf("quit : map - map = %d\n", b);
			return (NULL);
		}
	}
	coo = (int**)malloc(sizeof(int*) * a[0]);
	b = 0;
	while (*map)
	{
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		coo[b] = save_vector(b, a[0] / a[1], ft_atoihex(map));
		++b;
		while (ft_isdigit(*map) || *map == '+' || *map == '-')
			++map;
	}
	a[0]--;
	return(coo);
}

/*
** a[0] = number elems per line
** a[1] = number of lines
** b[0] = ou l on est sur la ligne du tableau
** b[1] = sur quelle ligne on est du tabeau
** xa = xabyab[0]
** xb = xabyab[1]
** ya = xabyab[2]
** yb = xabyab[3]
** couleur = xabyab[4]
** pdf[0] = point de fuite sur l abscisse X
** pdf[1] = poitnde fuite sur l ordonnée Y
*/

void		writing(void *mlx, void *win, int *a, int **input)
{
	int				b;
	int				xabyab[5];
	int				*vector;
	static int		**coo = NULL;

	coo = (input) ? input : coo;
	b = -1;
	while (++b < a[0])
	{
		vector = ft_param(coo[b], 0, 0);
//		printf("coo[%d] = %d, %d, %d\n", b, coo[b][2], coo[b][3], coo[b][4]);
		xabyab[0] = vector[2];
		xabyab[2] = vector[3];
		ft_memdel((void**)&vector);
		if (b < a[0] - (a[0] / a[1]))
		{
			vector = ft_param(coo[b + (a[0] / a[1])], 0, 0);
			xabyab[1] = vector[2];	
			xabyab[3] = vector[3];
//			printf("xa = %d ya = %d, xb = %d yb = %d\n", xabyab[0], xabyab[2], xabyab[1], xabyab[3]);
			ft_drawline(mlx, win, xabyab);
			ft_memdel((void**)&vector);
		}
		if (b % (a[0] / a[1]) < (a[0] / a[1]) - 1)
		{
			vector = ft_param(coo[b], 0, 0);
			xabyab[1] = vector[2];	
			xabyab[3] = vector[3];
//			printf("xa = %d ya = %d, xb = %d yb = %d\n", xabyab[0] , xabyab[2] , xabyab[1] , xabyab[3]);
			ft_drawline(mlx, win, xabyab);
			ft_memdel((void**)&vector);
		}
//		printf("\n");
	}
}

int		ft_display(int **coo, int *a)
{
	void			*mlx;
	void			*win;

	if (!coo)
		return (0);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1800, 1800, "mlx 42");
	writing(mlx, win, a, coo);
	mlx_key_hook(win, my_key_fct, 0);
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
	if (argc != 2)
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
	a[1] = 0;
	if (a[0] == -1 || ((a[0] = 1) && !(ft_display(ft_convert(map, a), a))))
		ft_putstr("error read or display\n");
	return (0);
}
