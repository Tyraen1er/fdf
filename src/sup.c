/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 23:23:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/12 01:19:43 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 

int		ft_color(int a, int *z)
{
	static int	zmin = 0;
	static int	ratio = 0;
	
	if (z)
	{
		zmin += (z < 0) ? -zmin : 0;
//		ratio = (0xFF0000 - 0xFF) / (z[1] - z[0]);
		ratio = 16 / (z[1] - z[0]);
		return (0);
	}
//	return (0xFF + (a - zmin) * ratio);
	return (0xFF << (a - zmin) * ratio);
}

void	shift(int *vector, int axe)
{
	static int	x = 10;
	static int	y = 10;

	if (axe == 'x' || axe == -'x')
	{
		x += (axe == 'x') ? 120 : -120;
//		x += (x < 0) ? -x : 0;
	}
	if (axe == 'y' || axe == -'y')
	{
		y += (axe == 'y') ? 120 : -120;
//		y += (y < 0) ? -y : 0;
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
	static double	x = 45;
	static double	y = 45;
	static double	z = 45;
	int			*ret[2];
	double		*rot;

	ret[0] = NULL;
	if (axe == 'x' || axe == -'x')
	{
		x += (axe == 'x') ? 0.1 : -0.1;
		x = (x < 0) ? 360 - x : x;
		x = (360 < x) ? x - 360 : x;
	}
	rot = (double[11]){3, 3, 1, 0, 0, 0, cos(x), -sin(x), 0, sin(x), cos(x)};
	if (vector)
		ret[0] = matrice_multi(rot, vector);
	if (axe == 'y' || axe == -'y')
	{
		y += (axe == 'y') ? 0.1 : -0.1;
		y = (y < 0) ? 360 - y : y;
		y = (360 < y) ? y - 360 : y;
	}
	rot = (double[11]){3, 3, cos(y), 0, sin(y), 0, 1, 0, -sin(y), 0 , cos(y)};
	if (vector)
	{
		ret[1] = ret[0];
		ret[0] = matrice_multi(rot, ret[1]);
		ft_memdel((void**)&ret[1]);
	}
	if (axe == 'z' || axe == -'z')
	{
		z += (axe == 'z') ? 0.1 : -0.1;
		z= (z < 0) ? 360 - z : z;
		z = (360 < z) ? z - 360 : z;
	}
	rot = (double[11]){3, 3, cos(z), -sin(z), 0, sin(z), cos(z), 0, 0, 0, 1};
	if (vector)
	{
		ret[1] = ret[0];
		ret[0] = matrice_multi(rot, ret[0]);
		ft_memdel((void**)&ret[1]);
	}
	return (ret[0]);
}

int		*matrice_multi(double *fst, int *scd)
{
	int	*ret;
	int	*tmp;
	int	x;
	int	y;
	int	a;

	y = -1;
	if (fst[0] != (scd[1]))
		return (NULL);
	ret = (int*)ft_memalloc(sizeof(int) * ((fst[1] * scd[0] + 2)));
	ret[0] = scd[0];
	ret[1] = fst[1];
	tmp = &ret[2];
	while (++y < ret[1] && (x = -1))
		while (++x < ret[0] && (a = -1))
			while (++a < fst[0])
				ret[(2 + x + y * scd[0])] +=
					fst[a + y * (int)fst[0] + 2] * scd[(a * scd[0] + x + 2)];
	return (ret);
}
