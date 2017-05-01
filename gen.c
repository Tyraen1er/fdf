t_par	*parsing(char *file)
{
	int		a;
	int		b;
	int		c;
	t_par	*pars;

	a = -1;
	pars = (s_pars)malloc(sizeof(s_wag));
	pars = {1, 0, 0, 0, NULL, NULL, NULL, NULL, NULL};
	if (!file)
		return (NULL);

/*
** nombre de lignes
** nombre d'int
** nombre de char
*/
	while (file[++a])
	{
		if (ft_isdigit(file[a]) && ++pars->allsizeint)
			while (ft_isdigit(file[a]))
				++a;
		if (ft_isletter(file[a]) && ++pars->allsizeword)
			while (ft_isletter(file[a]))
				++a;
		if (file[a] == '\n')
			++pars->nbl;
	}
	pars->allsize = a;
	pars->sizechar = (int*)malloc(sizeof(int) * nbl + 1);
	pars->sizeint = (int*)malloc(sizeof(int) * nbl + 1));
	pars->datachar = (char**)malloc(sizeof(char*) * nbl + 1));
	pars->dataint = (int**)malloc(sizeof(int*) * nbl + 1));
	pars->sizechar[nbl] = NULL;
	pars->sizeint[nbl] = NULL;
	pars->datachar[nbl] = NULL;
	pars->dataint[nbl] = NULL;
	a = 0;
	b = 0;
	c = 0;
	while(file[a] && ++b)
	{
		while (file[a] && file[a] != '\n')
		{
			++a;
			++pars->sizechar[b]
			if (ft_isdigit(file[a]) && ++pars->sizeint[b])
				while (ft_isdigit(file[a]))
				{
					++a;
					++pars->sizechar[b]
				}
		}
		pars->dataint[b] = (int*)malloc(sizeof(int) * pars->sizeint[b + 1]);
		pars->datachar[b] = (char*)malloc(sizeof(char) * pars->sizechar[b + 1]);
		pars->dataint[b] = NULL;
		pars->datachar[b] = NULL;
		while (file[a] && file[a] != '\n')
		{
			++a;
			++pars->sizechar[b]
			if (ft_isdigit(file[a]) && ++pars->sizeint[b])
				while (ft_isdigit(file[a]))
				{
					++a;
					++pars->sizechar[b]
				}
		}
		if (file[a] == '\n')
		{
			++c;
			++a;
		}
	}
}
