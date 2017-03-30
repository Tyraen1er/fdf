#include "fdf.h" 

int		ft_couleur(int a)
{
	if (-125 < a && a < 128)
		return (8388607 + a * 65535);
	return ((a < 128) ? 0xFFFFFF : 196732);
}

int		*rotate(int *vector, int axe, int var)
{
	static int	x = 45;
	static int	y = 45;
	static int	z = 45;
	float		rot[11];

	ft_bzero(rot, sizeof(int) * 11);
	if (axe == 'x')
	{
		x += (var == '+') ? 15 : -15; 
		rot[2] = 1;
		rot[6] = cos(x);
		rot[7] = -sin(x);
		rot[9] = sin(x);
		rot[10] = cos(x);
	}
	else if (axe == 'y')
	{
		y += (var == '+') ? 15 : -15; 
		rot[2] = cos(y);
		rot[4] = sin(y);
		rot[6] = 1;
		rot[8] = -sin(y);
		rot[10] = cos(y);
	}
	else
	{
		z += (var == '+') ? 15 : -15; 
		rot[2] = cos(z);
		rot[3] = -sin(z);
		rot[5] = sin(z);
		rot[6] = cos(z);
		rot[10] = 1;
	}
	return (matrice_multi(vector));
}

int		*matrice_multi(float *fst, float *scd)
{
	int	*ret;
	int	*tmp;
	int	x;
	int	y;
	int	a;

	y = -1;
	if (fst[0] != scd[1])
		return (NULL);
	ret = (int*)memalloc(sizeof(int) * (fst[1] * scd[0] + 2));
	ret[0] = scd[0];
	ret[1] = fst[1];
	tmp = &ret[2];
	while (++y < fst[1] && (x = -1))
		while (++x < scd[0] && (a = -1))
			while (++a < fst[0])
				ret[2 + x + y * scd[0]] +=
					fst[a + y * fst[0] + 2] * scd[a * scd[0] + x + 2];
	return (ret);
}
