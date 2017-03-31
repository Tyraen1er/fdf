/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 23:23:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/03/31 08:09:55 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h" 

int		ft_couleur(int a)
{
	if (-125 < a && a < 128)
		return (8388607 + a * 65535);
	return ((a < 128) ? 0xFFFFFF : 196732);
}

int		*shift(int *vector, int axe)
{
	static int	x = 10;
	static int	y = 10;

	if (axe == 'x' || axe == -'x')
		x += (axe == 'x') ? 120 : -120;
	if (axe == 'y' || axe == -'y')
		y += (axe == 'y') ? 120 : -120;
	if (vector)
		vector[2] += x;
	if (vector)
		vector[3] += y;
	return (vector);
}

int		*zoom(int *vector, int axe)
{
	int			*ret;
	static int	zoom = 1;

	ret = vector;
	if (axe == '+' || axe == '-')
		zoom += (axe == '+') ? 1 : -1;
	if (vector && 0 < zoom)
		ret[2] *= zoom;
	else if (vector)
		ret[2] /= abs(zoom - 2);
	if (vector && 0 < zoom)
		ret[3] *= zoom;
	else if (vector)
		ret[3] /= abs(zoom - 2);
	return (ret);
}

int		*rotate(int *vector, int axe)
{
	static int	x = 45;
	static int	y = 45;
	static int	z = 45;
	int			*ret;
	double		rot[11];

	ret = NULL;
	ft_bzero(rot, sizeof(double) * 11);
	if (axe == 'x' || axe == -'x')
		x += (axe == 'x') ? 15 : -15;
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
	rot[2] = cos(y);
	rot[4] = sin(y);
	rot[6] = 1;
	rot[8] = -sin(y);
	rot[10] = cos(y);

	if (ret)
		printf("ret[0] = %d et ret[1] = %d\n", ret[1], ret [2]);
	printf("est ce la que tu bug ?\n");
	if (vector)
		ret = matrice_multi(ret, rot);
	printf("est ce la que tu bug ?\n");
	
	ft_bzero(rot, sizeof(double) * 11);
	if (axe == 'z' || axe == -'z')
		z += (axe == 'z') ? 15 : -15;
	rot[2] = cos(z);
	rot[3] = -sin(z);
	rot[5] = sin(z);
	rot[6] = cos(z);
	rot[10] = 1;
	if (vector)
		ret = matrice_multi(ret, rot);
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
	if (fst[0] != (int)scd[1])
	{
		printf("c est la merde chef !!!\n");
		return (NULL);
	}
	ret = (int*)ft_memalloc(sizeof(int) * ((int)(fst[1] * scd[0] + 2)));
	ret[0] = scd[0];
	ret[1] = fst[1];
	tmp = &ret[2];
	while (++y < fst[1] && (x = -1))
		while (++x < scd[0] && (a = -1))
			while (++a < fst[0])
				ret[(int)(2 + x + y * scd[0])] +=
					fst[a + y * fst[0] + 2] * scd[(int)(a * scd[0] + x + 2)];
	return (ret);
}
