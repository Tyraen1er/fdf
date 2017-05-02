/*
** nbl = nombre ligne
** allsize = taille du fichier en octet / nombre caractere dans le fichier
** allsizeint = nombre d'int
** sizechar = taille ligne
** sizeword = nombre mot sur la ligne
** sizeint = nombre int sur la ligne
** dataint = les int par ligne
*** dataword = les mots par ligne
** datachar = les lignes
*/

typedef struct			s_pars
{
	int					nbl;
	int					allsize;
	int					allsizeint;
	int					allsizeword;
	int					*sizechar;
	int					*sizeint;
	int					**typedataint;
	long long			**dataint;
	char				**datachar;
}						t_pars;
