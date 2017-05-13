/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 23:23:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/13 07:59:59 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 

int		ft_color(int *xabyab, int *z, int modif)
{
	static int	zmin = 0;
	static int	ratio = 0;
	static int	a = 0;
	static int	b = 0;
	static int	degrade = 0;
	
	if (z)
	{
		zmin += (z < 0) ? -zmin : 0;
		ratio = 16 / (z[1] - z[0]);
		return (0);
	}
	if (xabyab)
	{
		a = (modif == 1) ? 0xFF << (xabyab[4] - zmin) * ratio : xabyab[4];
		b = (modif == 1) ? 0xFF << (xabyab[5] - zmin) * ratio : xabyab[5];
		if (!(degrade = 0) && abs(xabyab[0] - xabyab[1]) != abs(xabyab[2] - xabyab[3]))
			degrade = (abs(xabyab[0] - xabyab[1]) >= abs(xabyab[2] - xabyab[3])) ?
				(10 * abs(a - b)) / abs(xabyab[0] - xabyab[1]) : 
				(10 * abs(a - b)) / abs(xabyab[2] - xabyab[3]);
		a *= 10;
		b *= 10;
		degrade = (a < b) ? degrade : -degrade;
		return (0);
	}
	if ((degrade < 0 && b < a) ||(0 < degrade && a < b))
		a += degrade;
	return (a / 10);
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
	static double	x = M_PI_4;
	static double	y = M_PI_4;
	static double	z = M_PI_4;
	int			*ret[2];
	double		*rot;

	ret[0] = NULL;
	if (axe == 'x' || axe == -'x')
	{
		x += (axe == 'x') ? M_PI / 16 : -M_PI / 16;
//		x = (x < 0) ? 2 * M_PI - x : x;
//		x = (2 * M_PI < x) ? x - 2 * M_PI : x;
	}
	rot = (double[11]){3, 3, 1, 0, 0, 0, cos(x), -sin(x), 0, sin(x), cos(x)};
	if (vector)
		ret[0] = matrice_multi(rot, vector);
	if (axe == 'y' || axe == -'y')
	{
		y += (axe == 'y') ? M_PI / 16 : -M_PI / 16;
//		y = (y < 0) ? 2 * M_PI - y : y;
//		y = (2 * M_PI < y) ? y - 2 * M_PI : y;
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
		z += (axe == 'z') ? M_PI / 16 : -M_PI / 16;
//		z = (z < 0) ? 2 * M_PI - z : z;
//		z = (2 * M_PI < z) ? z - 2 * M_PI : z;
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
