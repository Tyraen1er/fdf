#include "libft.h"
#include <fcntl.h>

void ft_display()
{
	ft_putstr("tout semble fonctionner\n");
}

void	ft_parsing(char *file)
{
	char	*tmp;
	int		**coo;
	int		a;
	int		b;

	a = 0;
	tmp = file;
	while (*file)
	{
		if (ft_isdigit(*file) && ++a)
			while (ft_isdigit(*file) && *file)
				++file;
		++file;
	}
	if (a % 3)
	{
		ft_putstr("mauvais manque des coordonnees");
		return ;
	}
	coo = (int**)malloc(sizeof(int*) * a / 3);
	file = tmp;
	a = 0;
	while (*file)
	{
		b = 0;
		if (ft_isdigit(*file))
		{
			coo[a] = malloc(sizeof(int) * 3);
			while (b != 2 && *file)
			{
				if (ft_isdigit(*file) && ++b)
					coo[a][b] = ft_atoi(file);
				++file;
			}
		}
		++file;
	}
	ft_display(coo);
}

int main(int ac, char **av)
{
	char	*file;
	char	*tmp;
	char	buf[151];
	int		a;
	int		b;

	if (ac != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	a = open(av[1], O_RDONLY);
	buf[150] = 0;
	file = ft_memalloc(1);
	while (0 < (b = read(a, buf, 150)))
	{
		tmp = file;
		file = ft_strjoin(file, buf);
		free(tmp);
	}
	if (b == -1 || a == -1 || !file)
		ft_putstr("error reading\n");
	ft_parsing(file);
	return (0);
}
