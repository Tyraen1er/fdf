/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 07:33:09 by eferrand          #+#    #+#             */
/*   Updated: 2017/03/22 04:32:01 by eferrand         ###   ########.fr       */
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
	int     c;
	int     b;
	int     **coo;
	char    *tmp;

	c = 0;
	tmp = map - 1;
	while (*++tmp && ((map < tmp && *(tmp - 1) == '\n'
					&& ft_isdigit(*tmp) && ++a[1]) || (1)))
	{
		if ((ft_isdigit(*tmp) || *++tmp == '-' || *(tmp - 1) == '+') && ++a[0])
			while (ft_isdigit(*tmp))
				++tmp;
		else
			return (NULL);
	}
	coo = (int**)malloc(sizeof(int*) * a[0]);
	b = 0;
	while (*map)
	{
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		if ((ft_isdigit(*map) || *map == '-' || *map == '+') &&
				(coo[b] = save_vector(b, a[0] / a[1], ft_atoi(map))))
		{
			while ((ft_isdigit(*map) || *map == '-' || *map == '+'))
				++map;
			++b;
		}
	}
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
** pdf[0] = point de fuite sur l abscisse X
** pdf[1] = poitnde fuite sur l ordonnée Y
*/

void		writing(int *a, int *b, int **coo)
{

// Il faut afficher tous les segments a la suite
// int	b vraiment utile ?
	xabyab[0] = ;
	xabyab[1] = ;
	xabyab[2] = ;
	xabyab[3] = ;
	ft_drawline(mlx, win, xabyab);
}

int		ft_display(int **coo, int *a)
{
	int				b[2];
	int				xabyab[4];
	void			*mlx;
	void			*win;

	b[0] = -1;
	a[0] /= a[1];
	b[1] = a[1];
	if (!coo)
		return (0);
	mlx = mlx_init(void);
	win = mlx_new_window(mlx, 2000, 2000, "mlx 42");
	writing(a, b, coo);
	mlx_key_hook(win, my_key_fct);
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
