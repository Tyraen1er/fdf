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
	{
		while (++x < scd[0] && (a = -1))
		{
//			printf("debut case\n");
			while (++a < fst[0])
			{
//				printf("\nx = %d\ny = %d\na = %d\n", x, y, a);
//				printf("%d * %d\n" ,fst[a + y * fst[0] + 2] , scd[a * scd[0] + x + 2]);
//				printf("position case 1 = %d\nposition case 2 = %d\n", a + y * fst[0] + 2, a * scd[0] + x + 2);
//				printf("case qu on remplie : %d\n", 2 + x + y * scd[0]);
//				printf("%d, ", fst[a + y * fst[0]] * scd[2 + a * scd[0] + x]);
				ret[2 + x + y * scd[0]] += fst[a + y * fst[0] + 2] * scd[a * scd[0] + x + 2];
//				printf("ret = %d\n", ret[2 + x + y * scd[0]]);
			}
//			printf("\nune case finie\n\n");
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

	fst[0] = 3;
	fst[1] = 3;
	
	fst[2] = 3;
	fst[3] = 4;
	fst[4] = 5;
	fst[5] = 2;
	fst[6] = 7;
	fst[7] = 2;
	fst[7] = 1;
	fst[7] = 9;
	fst[7] = 6;


	scd[0] = 3;
	scd[1] = 3;
	
	scd[2] = 2;
	scd[3] = 7;
	scd[4] = 1;
	scd[5] = 5;
	scd[6] = -3;
	scd[7] = 8;
	scd[7] = 18;
	scd[7] = 1;
	scd[7] = -4;

	ret = matrice_multi(fst, scd);
	a = 0;
	while (a < 11)
		printf("%d, ", ret[a++]);
	printf("\n");
	return (0);
}
