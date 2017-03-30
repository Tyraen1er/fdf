int		translate_number(keycode)
{
	if (keycode == 29 || keycode == 82)
		return ('0');
	if (keycode == 18 || keycode == 83)
		return ('1');
	if (keycode == 19 || keycode == 84)
		return ('2');
	if (keycode == 20 || keycode == 85)
		return ('3');
	if (keycode == 21 || keycode == 86)
		return ('4');
	if (keycode == 23 || keycode == 87)
		return ('5');
	if (keycode == 22 || keycode == 88)
		return ('6');
	if (keycode == 26 || keycode == 89)
		return ('7');
	if (keycode == 28 || keycode == 91)
		return ('8');
	return ('9');
}

int		transl(int keycode)
{
	if (keycode == 17)
		return ('t');
	if (keycode == 32)
		return ('u');
	if (keycode == 9)
		return ('v');
	if (keycode == 13)
		return ('w');
	if (keycode == 7)
		return ('x');
	if (keycode == 16)
		return ('y');
	if (keycode == 6)
		return ('z');
	else
		return (translate_number(keycode));
}

int		translate(int keycode)
{
	if (keycode == 44)
		return ('/');
	if (keycode == 00)
		return ('a');
	if (keycode == 11)
		return ('b');
	if (keycode == 8)
		return ('c');
	if (keycode == 02)
		return ('d');
	if (keycode == 14)
		return ('e');
	if (keycode == 03)
		return ('f');
	if (keycode == 05)
		return ('g');
	if (keycode == 04)
		return ('h');
	if (keycode == 34)
		return ('i');
	if (keycode == 38)
		return ('j');
	else
		return(translate(keycode));
}

int		translator(int keycode)
{
	if (keycode == 40)
		return ('k');
	if (keycode == 37)
		return ('l');
	if (keycode == 46)
		return ('m');
	if (keycode == 45)
		return ('n');
	if (keycode == 31)
		return ('o');
	if (keycode == 35)
		return ('p');
	if (keycode == 12)
		return ('q');
	if (keycode == 15)
		return ('r');
	if (keycode == 01)
		return ('s');
	else
		return(transl(keycode));
}
