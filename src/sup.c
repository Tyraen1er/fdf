/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 04:03:37 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/29 04:03:38 by eferrand         ###   ########.fr       */
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
	a = 0;
	if (nb[b] != '0' || nb[b + 1] != 'x')
		return (atoi(nb));
	nb += 2;
	while (nb[a] != ' ' && nb[a] != '\t' && nb[a] != '\n' && nb[a] &&
			nb[a] != ',')
		++a;
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

int		*ft_param(int *vector, int axe, int color)
{
	int		a;
	int		*ret;

	ret = (vector) ? (int*)malloc(sizeof(int) * 5) : NULL;
	a = -1;
	while (vector && ++a < 5)
		ret[a] = vector[a];
	scaling(ret, (color == 1) ? axe : 0);
	ret = rotate(ret, (color == 3) ? axe : 0);
	shift(ret, (color == 2) ? axe : 0);
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
	static int		erase = 1;

	color = (keycode == 8) ? -color : color;
	if (keycode == 53)
		exit(3);
	if ((keycode == 117 && (erase = -erase)) || 0 < erase)
		writing(all, ((void**)all)[2], 0);
	if (keycode == 123 || keycode == 124)
		ft_param(NULL, (keycode == 123) ? -'x' : 'x', 2);
	if (keycode == 125 || keycode == 126)
		ft_param(NULL, (keycode == 126) ? -'y' : 'y', 2);
	if (keycode == 69 || keycode == 78)
		ft_param(NULL, (keycode == 69) ? '+' : '-', 1);
	if (keycode == 91 || keycode == 84)
		ft_param(NULL, (keycode == 91) ? 'x' : -'x', 3);
	if (keycode == 86 || keycode == 88)
		ft_param(NULL, (keycode == 86) ? 'y' : -'y', 3);
	if (keycode == 75 || keycode == 67)
		ft_param(NULL, (keycode == 75) ? 'z' : -'z', 3);
	writing(all, ((void**)all)[2], color);
	return (0);
}
