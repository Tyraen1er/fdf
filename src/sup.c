#include "fdf.h" 

int		ft_couleur(int a)
{
	if (-125 < a && a < 128)
		return (8388607 + a * 65535);
	return ((a < 128) ? 0xFFFFFF : 196732);
}

int		*matrice_multi(int *fst, int *scd)
{
	int	*ret;
	int	*tmp;
	int	x;
	int	y;
	int	a;

	y = -1;
	if (fst[0] != scd[1])
		return (NULL);
	ret = (int*)malloc(sizeof(int) * (fst[1] * scd[0] + 2));
	ft_bzero(ret, sizeof(int) * (fst[1] * scd[0] + 2));
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
