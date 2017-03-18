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
*/

int		*matrice_multi(int *fst, int *scd)
{
	int	*ret;
	int	*tmp;
	int	a;
	int	b;
	int	c;

	ret = 0;
	b = -1;
	c = 0;
	if (fst[0] != scd[1])
		return (NULL);
	ret = (int*)malloc(sizeof(int) * (fst[1] * scd[0] + 2));
	ft_bzero(ret, sizeof(int) * (fst[1] * scd[0] + 2));
	ret[0] = scd[0];
	ret[1] = fst[1];
	tmp = &ret[2];
	while (++b < fst[1] && (a = - 1))
	{
		while (a < scd[0] && (c = - 1))
		{
			while (++c < scd[0])
			{
				ret[] = fst[] * scd[];
			}
		}
	}
	printf("fin multiplication\n\n");
	return (ret);
}

int main()
{
	int	a;
	int	fst[8];
	int	scd[8];
	int	*ret;

	fst[0] = 2;
	fst[1] = 3;
	
	fst[2] = 1;
	fst[3] = 1;
	fst[4] = 1;
	fst[5] = 1;
	fst[6] = 1;
	fst[7] = 1;


	scd[0] = 3;
	scd[1] = 2;
	
	scd[2] = 1;
	scd[3] = 1;
	scd[4] = 1;
	scd[5] = 1;
	scd[6] = 1;
	scd[7] = 1;

	ret = matrice_multi(fst, scd);
	a = 0;
	while (a < 11)
		printf("%d, ", ret[a++]);
	printf("\n");
	return (0);
}
