#include <stdio.h>
#include <stdlib.h>

void    ft_bzero(void *tab, size_t n)
{
	while (n--)
		((char *)tab)[n] = 0;
}

/*
** fst[0] = taille x
** fst[1] = taille y
** a = position ligne matrice fst
** b = position colone matrice fst
** c = pointeur de multiplication
*/

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
				ret[2 + x + y * scd[0]] += fst[a + y * fst[0] + 2] * scd[a * scd[0] + x + 2];
	return (ret);
}
