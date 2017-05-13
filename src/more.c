/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 02:51:07 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/13 05:58:26 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Ne fonctionne que pour ce programme precis
*/

int		ft_atoifdf(char *nb)
{
	int		ret;
	int		a;
	int		b;

	ret = 0;
	b = 0;
	a = ft_strlen(nb);
	if (nb[b] != '0' || nb[b + 1] != 'x')
		return (atoi(nb));
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

int		*ft_param(int *vector, int axe, int modif)
{
	int		a;
	int		*ret;

	ret = (vector) ? (int*)malloc(sizeof(int) * 5) : NULL;
	a = -1;
	while (vector && ++a < 5)
		ret[a] = vector[a];
	scaling(ret, (modif == 1) ? axe : 0);
/*
	Cette mechante bestiole contient un segfault, il est donc enfermé pour la
	securité de tous.
	Merci de ne pas le libérer !
	Nan je deconne mais l affichage n est plus cohérent avec lui dans les
	parages...
*/
	ret = rotate(ret, (modif == 3) ? axe : 0);
	shift(ret, (modif == 2) ? axe : 0);
	return (ret);
}

/*
** 123 = gauche ||| 124 = droite ||| 125 = bas ||| 126 = haut
** 69 = + ||| 78 = -
** 91 = 8 ||| 84 = 2 ||| 86 = 4 ||| 88 = 6 ||| 75 = / ||| 67 = * 
** 8 = c ||| 
*/

int		my_key_fct(int keycode, void *all)
{
	static int		color = 1;

//	printf("%d\n", keycode);
	color = (keycode == 8) ? -color : color;
	if (keycode == 53)
		exit(3);
	writing(all, ((void**)all)[2], 0);
	if (keycode == 123 || keycode == 124)
		ft_param(NULL, (keycode == 123) ? -'x' : 'x', 2);
	if (keycode == 125 || keycode == 126)
		ft_param(NULL, (keycode == 126) ? -'y' : 'y', 2);
	if (keycode == 69 || keycode == 78)
		ft_param(NULL, (keycode == 69) ? '+' : '-' , 1);
	if (keycode == 91 || keycode == 84)
		ft_param(NULL, (keycode == 91) ? 'x': -'x', 3);
	if (keycode == 86 || keycode == 88)
		ft_param(NULL, (keycode == 86) ? 'y': -'y', 3);
	if (keycode == 75 || keycode == 67)
		ft_param(NULL, (keycode == 75) ? 'z': -'z', 3);
	writing(all, ((void**)all)[2], color);
	return (0);
}
/*
void	delineation(void **all, int *xabyab, int color)
{
}
*/
void    ft_drawline(void **all, int *xabyab, int modif)
{
	int		a[4];

	a[0] = xabyab[0];
	a[1] = xabyab[2];
	a[2] = (xabyab[0] < xabyab[1]) ? 1 : -1;
	a[3] = (xabyab[2] < xabyab[3]) ? 1 : -1;
	ft_color(xabyab, NULL, modif);
	if (!(xabyab[1] - xabyab[0]) && !(xabyab[3] - xabyab[2]))
		mlx_pixel_put(all[0], all[1], a[0], a[1], ft_color(NULL, NULL, 0));
	else if (abs(xabyab[0] - xabyab[1]) < abs(xabyab[2] - xabyab[3]))
		while ((a[3] == 1 && a[1] < xabyab[3]) || (a[3] == -1 && a[1] > xabyab[3]))
		{
			if (((xabyab[1] - xabyab[0]) * a[1]) / (xabyab[3] - xabyab[2]) !=
				((xabyab[1] - xabyab[0]) * (a[1] - 1)) / (xabyab[3] - xabyab[2]))
				a[0] += a[2];
			mlx_pixel_put(all[0], all[1], a[0], a[1], ft_color(NULL, NULL, 0));
			a[1] += a[3];
		}
	else
		while ((a[2] == 1 && a[0] < xabyab[1]) || (a[2] == -1 && a[0] > xabyab[1]))
		{
			if (((xabyab[3] - xabyab[2]) * a[0]) / (xabyab[1] - xabyab[0]) !=
				((xabyab[3] - xabyab[2]) * (a[0] - 1)) / (xabyab[1] - xabyab[0]))
				a[1] += a[3];
			mlx_pixel_put(all[0], all[1], a[0], a[1], ft_color(NULL, NULL, 0));
			a[0] += a[2];
		}
}
