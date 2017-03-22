#include <stdio.h>
#include "libft.h"

int		*save_vector(int pos, int sizeline, int z)
{
	int		*vector;

	vector = (int*)malloc(sizeof(int) * 5);
	vector[0] = 1;
	vector[1] = 3;
	vector[3] = pos / sizeline;
	vector[2] = pos - (vector[3] * sizeline);
	vector[4] = z;
	return (vector);
}

int		**ft_convert(char *map, int *a)
{
	int		c;
	int		b;
	int		**coo;
	char	*tmp;

	c = 0;
	tmp = map - 1;
	while (*++tmp && ((map < tmp && *(tmp - 1) == '\n'
					&& ft_isdigit(*tmp) && ++a[1]) || (1)))
	{
		if ((ft_isdigit(*tmp) || *++tmp == '-' || *(tmp - 1) == '+') && ++a[0])
			while (ft_isdigit(*tmp))
				++tmp;
		else
			return (NULL);
	}
	coo = (int**)malloc(sizeof(int*) * a[0]);
	b = 0;
	while (*map)
	{
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		if (ft_isdigit(*map) || *map == '-' || *map == '+')
		{
			coo[b] = save_vector(b, a[0] / a[1], ft_atoi(map));
			while (ft_isdigit(*map) || *map == '-' || *map == '+')
				++map;
			++b;
		}
	}
	return(coo);
}

int main()
{
	int		b;
	int		c;
	int		d;
	char	*map;
	int		a[2];
	int		**coo;

	a[0] = 0;
	a[1] = 1;
	b = -1;
	c = -1;
	d = 0;
	map = (char*)malloc(17);
	map[0] = '5';
	map[1] = ' ';
	map[2] = '1';
	map[3] = ' ';
	map[4] = '5';
	map[5] = ' ';
	map[6] = '3';
	map[7] = '\n';
	map[8] = '8';
	map[9] = ' ';
	map[10] = '0';
	map[11] = ' ';
	map[12] = '2';
	map[13] = ' ';
	map[14] = '9';
	map[15] = '\n';
	map[16] = 0;
	coo = ft_convert(map, a);
	/*while (++b < a[0])
	{
		c = -1;
		while (++c < coo[b][0] * coo[b][1] + 2)
			printf("coo[%d][%d] = %d\n", b, c, coo[b][c]);
	}*/
	return (0);
}
