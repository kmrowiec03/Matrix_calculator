#include<stdio.h>
#include<stdlib.h>
#define MAX_ERR 5
static char* p[] = { "",
" zle dane",
" otwarcie pliku",
" brak pamieci",
" czytanie macierzy ",
" nieznany ",
};
void error(int nr, char* str)
{
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	fprintf(stderr, "\nBlad(%d) - %s %s\n", nr, p[k], str);
	exit(nr);
}
