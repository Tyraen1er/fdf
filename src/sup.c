/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 23:23:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/04 02:26:11 by eferrand         ###   ########.fr       */
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
		x += (axe == 'x') ? 120 : -120;
	if (axe == 'y' || axe == -'y')
		y += (axe == 'y') ? 120 : -120;
	if (vector)
	{
		vector[2] += x;
		vector[3] += y;
	}
}

void	zoom(int *vector, int axe)
{
	static int	zoom = 10;

	if (axe == '+' || axe == '-')
	{
		zoom += (axe == '+') ? 1 : -1;
		return ;
	}
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
	int			*ret;
	int			*tmp;
	double		*rot;

	rot = (double[11]){0};
	ret = NULL;
	ft_bzero(rot, sizeof(double) * 11);
	if (axe == 'x' || axe == -'x')
		x += (axe == 'x') ? 15 : -15;
	rot[0] = 3;
	rot[1] = 3;
	rot[2] = 1;
	rot[6] = cos(x);
	rot[7] = -sin(x);
	rot[9] = sin(x);
	rot[10] = cos(x);

	if (vector)
		ret = matrice_multi(vector, rot);
	ft_bzero(rot, sizeof(double) * 11);
	if (axe == 'y' || axe == -'y')
		y += (axe == 'y') ? 15 : -15;
	rot[0] = 3;
	rot[1] = 3;
	rot[2] = cos(y);
	rot[4] = sin(y);
	rot[6] = 1;
	rot[8] = -sin(y);
	rot[10] = cos(y);

	if (vector)
	{
		tmp = ret;
		ret = matrice_multi(tmp, rot);
		ft_memdel((void**)&tmp);
	}
	ft_bzero(rot, sizeof(double) * 11);
	if (axe == 'z' || axe == -'z')
		z += (axe == 'z') ? 15 : -15;
	rot[0] = 3;
	rot[1] = 3;
	rot[2] = cos(z);
	rot[3] = -sin(z);
	rot[5] = sin(z);
	rot[6] = cos(z);
	rot[10] = 1;
	if (vector)
	{
		tmp = ret;
		ret = matrice_multi(ret, rot);
		ft_memdel((void**)&tmp);
	}
	return (ret);
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
	{
		printf("c est la merde chef !!!\n");
		return (NULL);
	}
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
