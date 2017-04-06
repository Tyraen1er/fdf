/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 02:51:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/04/05 03:47:44 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Ne fonctionne que pour ce programme precis
*/

int     *save_vector(int pos, int sizeline, int z)
{
	int     *vector;

	vector = (int*)malloc(sizeof(int) * 5);
	vector[0] = 1;
	vector[1] = 3;
	vector[3] = pos / sizeline;
	vector[2] = pos - (vector[3] * sizeline);
	vector[4] = z;
    return (vector);
}

int		ft_atoihex(char *nb)
{
	int		ret;
	int		a;
	int		b;

	ret = 0;
	b = 0;
	a = ft_strlen(nb);
	while (a--)
	{
		if ('0' <= nb[a] && nb[a] <= '9')
			ret += (nb[a] - '0') << (b * 4);
		if ('a' <= nb[a] && nb[a] <= 'f')
			ret += (nb[a] - 'a' + 10) << (b * 4);
		if ('A' <= nb[a] && nb[a] <= 'F')
			ret += (nb[a] - 'A' + 10) << (b * 4);
		++b;
	}
	return (ret);
}

// not finish
int		*ft_param(int *vector, int axe, int modif)
{
	int		a;
	int		*ret;

	ret = (int[5]){0};
	a = -1;
	while (++a < 5)
		ret[a] = vector[a];
	zoom(ret, (modif == 1) ? axe : 0);
	ret = rotate(ret, (modif == 3) ? axe : 0);
	shift(ret, (modif == 2) ? axe : 0);
	return (ret);
}

int		my_key_fct(int keycode, void *pdf)
{
	static char		commande[20];
	static int		a = 0;

	(void)pdf;
	if (keycode == 53)
		exit(3);
	printf("il se passe quelquechose\n%d\n", keycode);
	if (keycode == 123 || keycode == 124)
		ft_param(NULL, (keycode == 123) ? -'x' : 'x', 2);
	if (keycode == 125 || keycode == 126)
		ft_param(NULL, (keycode == 126) ? -'x' : 'x', 2);
	if (*commande == '/' || keycode == 44)
	{
		if (keycode == 44 && a)
		{
			ft_bzero(commande, 20);
			*commande = '/';
		}
// entree = 36
		if (keycode != 36)
			commande[a++] = translator(keycode);
		if (keycode == 36)
			;
//			ft_param(commande);
	}
	return (0);
}

void    ft_drawline(void *mlx, void *win, int *xabyab)
{
	int     xav;
	int     yav;
	int     x;
	int     y;

	x = xabyab[0];
	y = xabyab[2];
	xav = (xabyab[0] < xabyab[1]) ? 1 : -1;
	yav = (xabyab[2] < xabyab[3]) ? 1 : -1;
	if (!(xabyab[1] - xabyab[0]) && !(xabyab[3] - xabyab[2]))
		mlx_pixel_put(mlx, win, x, y, xabyab[4]);
	else if (abs(xabyab[0] - xabyab[1]) < abs(xabyab[2] - xabyab[3]))
		while ((yav == 1 && y < xabyab[3]) || (yav == -1 && y > xabyab[3]))
		{
			if (((xabyab[1] - xabyab[0]) * y) / (xabyab[3] - xabyab[2]) != ((xabyab[1] - xabyab[0]) * (y - 1)) / (xabyab[3] - xabyab[2]))
				x += xav;
			mlx_pixel_put(mlx, win, x, y, xabyab[4]);
			y += yav;
		}
	else
		while ((xav == 1 && x < xabyab[1]) || (xav == -1 && x > xabyab[1]))
		{
			if (((xabyab[3] - xabyab[2]) * x) / (xabyab[1] - xabyab[0]) != ((xabyab[3] - xabyab[2]) * (x - 1)) / (xabyab[1] - xabyab[0]))
				y += yav;
			mlx_pixel_put(mlx, win, x, y, xabyab[4]);
			x += xav;
		}
}
