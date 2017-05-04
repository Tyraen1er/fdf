t_line		*ft_convert(char *map)
{
	int		a;
	int		l;
	t_line	*line;

	a = 0;
	l = 1;
	while (*map && !(ft_isdigit(*map)))
		++map;
	if (ft_isdigit(*map))
		createline();
	while (map[a)
		while (map[a] != '\n' && map[a])
		{
			while (map[a] == ' ' || map[a] == '\t' || map[a] == '\n')
				++a;
			if (ft_isdigit(map[a]))
			{
				ft_atoifdf(map[a])
					while (ft_isdigit(map[a]))
						++a;
				if (map[a] == ',')
				{
					ft_atoifdf(map[a])
						if (map[a] == '0' && map[a + 1] == 'x')
							a += 2;
					while (ft_isdigit(map[a]))
						++a;
				}
				if (map[a] == '\n')
				{
					++l;
				}
			}
		}
}

int  main()
{
	int		fd;
	int		a;
	char	buf[151];
	char	*map;
	char	*tmp;

	map = ft_memalloc(1);
	if (argc != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((a = read(fd, buf, 150)) && a != -1)
	{
		buf[a] = 0;
		tmp = ft_strjoin(map, buf);
		ft_memdel((void *)&map);
		map = tmp;
	}
	if (a == -1 || ((a = 1) && !(ft_display(ft_convert(map), a))))
		ft_putstr("error read or display\n");
	return (0);
}
