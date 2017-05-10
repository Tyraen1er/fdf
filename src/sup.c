/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 23:23:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/10 07:14:28 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 

int		ft_couleur(int a)
{
	if (-125 < a && a < 128)
		return (8388607 + a * 65535);
	return ((a < 128) ? 0xFFFFFF : 196732);
}

void	shift(int *vector, int axe)
{
	static int	x = 10;
	static int	y = 10;

	if (axe == 'x' || axe == -'x')
	{
		x += (axe == 'x') ? 120 : -120;
		x += (x < 0) ? -x : 0;
	}
	if (axe == 'y' || axe == -'y')
	{
		y += (axe == 'y') ? 120 : -120;
		y += (y < 0) ? -y : 0;
	}
	if (vector)
	{
		vector[2] += x;
		vector[3] += y;
	}
}

void	scaling(int *vector, int axe)
{
	static int	zoom = 10;

	if (axe == '+' || axe == '-')
		zoom += (axe == '+') ? 1 : -1;
	if (!vector)
		return ;
	if (0 < zoom)
	{
		vector[2] *= zoom;
		vector[3] *= zoom;
		vector[4] *= zoom;
	}
	else
	{
		vector[2] /= -(zoom - 2);
		vector[3] /= -(zoom - 2);
		vector[4] /= -(zoom - 2);
	}
}

int		*rotate(int *vector, int axe)
{
	static int	x = 45;
	static int	y = 45;
	static int	z = 45;
	int			*ret[2];
	double		*rot;

	ret[0] = NULL;
	if (axe == 'x' || axe == -'x')
	{
		x += (axe == 'x') ? 15 : -15;
		x = (x < 0) ? 360 - x : x;
		x = (360 < x) ? x - 360 : x;
	}
	rot = (double[11]){3, 3, 1, 0, 0, 0, cos(x), -sin(x), 0, sin(x), cos(x)};
	if (vector)
		ret[0] = matrice_multi(vector, rot);
	if (axe == 'y' || axe == -'y')
	{
		y += (axe == 'y') ? 15 : -15;
		y = (y < 0) ? 360 - y : y;
		y = (360 < y) ? y - 360 : y;
	}
	rot = (double[11]){3, 3, cos(y), 0, sin(y), 0, 1, 0, -sin(y), 0 , cos(y)};
	if (vector)
	{
		ret[1] = ret[0];
		ret[0] = matrice_multi(ret[1], rot);
		ft_memdel((void**)&ret[1]);
	}
	if (axe == 'z' || axe == -'z')
	{
		z += (axe == 'z') ? 15 : -15;
		z= (z < 0) ? 360 - z : z;
		z = (360 < z) ? z - 360 : z;
	}
	rot = (double[11]){3, 3, cos(z), -sin(z), 0, sin(z), cos(z), 0, 0, 0, 1};
	if (vector)
	{
		ret[1] = ret[0];
		ret[0] = matrice_multi(ret[0], rot);
		ft_memdel((void**)&ret[1]);
	}
	return (ret[0]);
}

int		*matrice_multi(int *fst, double *scd)
{
	int	*ret;
	int	*tmp;
	int	x;
	int	y;
	int	a;

	y = -1;
	if (fst[1] != (int)scd[0])
		return (NULL);
	ret = (int*)ft_memalloc(sizeof(int) * ((int)(fst[1] * scd[0] + 2)));
	ret[0] = scd[0];
	ret[1] = fst[1];
	tmp = &ret[2];
	while (++y < ret[1] && (x = -1))
		while (++x < ret[0] && (a = -1))
			while (++a < fst[0])
				ret[(int)(2 + x + y * scd[0])] +=
					fst[a + y * fst[0] + 2] * scd[(int)(a * scd[0] + x + 2)];
	return (ret);
}
