#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#pragma warning( disable : 4996 )

int n;
extern void error(int, char*);
void generowanie_macierzy(FILE* fw, double** tab, int n);
void odczytaj_wymiary_pliku(FILE* fd, int* wiersze, int* kolumny);
void funkcja(double* a, int n, int opcja1, int opcja2);
double srednia_geo(int n, double* x);
void odczytaj_wymiary_wektora(FILE* fd, int* kolumny);
int main() {
	FILE* fd, * fw, * fz;

	int wybor;
	double** tw = NULL;
	printf("\nWybierz\n0 - jesli chcesz zamknac program\n1 - jesli chcesz wygenerowac macierz i zapiac do pliku\n2 - jesli chcesz wykonac zadania\n\nwybor: ");
	if (!(scanf("%d", &wybor)))error(1, "(zle wczytana liczba)");

	if (wybor == 0)
	{
		printf("\nZamknales program. Zapraszmy ponownie:)");
		return 0;
	}
	else if (wybor == 1)
	{
		if (!(fw = fopen("dane.txt", "w"))) error(2, "podczas zapisywania");

		printf("Jakiego wymiaru ma byc macierz A[n][n]. Podaj n: ");
		if (!(scanf("%d", &n)))error(1, "(zle wczytana liczba)");
		generowanie_macierzy(fw, tw, n);
		if (tw) {
			for (int i = 0; i < n; i++)
			{
				if (tw[i])
				{
					free(tw[i]);
				}
			}
			free(tw);
			tw = NULL;
		}

		fclose(fw);
	}
	else if (wybor == 2)
	{
		if (!(fd = fopen("dane.txt", "r"))) error(2, "podczas sczytywania");
		int kolumny = 1, wiersze = 0;//ustawienie na rozne wartosci
		odczytaj_wymiary_pliku(fd, &wiersze, &kolumny);
		//printf("\n%d % d", wiersze, kolumny);
		if (wiersze == kolumny)
		{
			n = wiersze;
			rewind(fd);
			double* A;

			if (!(A = (double*)malloc(sizeof(double) * n * n)))
				error(3, "(alokacja 1)");

			for (int i = 0; i < n * n; i++)//sczytanie macierzy z pliku do tablicy jednowymiarowej A
			{
				if (!(fscanf(fd, "%lf", &A[i])))error(4, "(bledny znak w macierzy)");
			}
			int wypisz;
			printf("\nWybierz\n 1 - jesli chcesz wypisac macierz ktora bedzie w tablicy A\n 2 - jesli chcesz przejsc bez wypisywania\n Wybor: ");
			if (!(scanf("%d", &wypisz)))error(1, "(zle wczytana liczba)");
			printf("\n");
			if (wypisz == 1)
			{
				for (int j = 0; j < n * n; j++)//wypisywanie macierzy w konsoli
				{
					printf("%.2lf", A[j]);
					printf(" ");
					if (j != 0 && (j + 1) % n == 0)printf("\n");
				}
			}
			else if (wypisz == 2)printf("\nNie wypisujesz macierzy\n");
			else error(1, "(bledna liczba)");

			int opcja1 = 0, opcja2 = 0;
			printf("\nWybierz co chcesz zrobic\n\n0 - obliczyc srednia geometryczna dodatnich elementow wektora x\n1 - obliczyc srednia geometryczna dodatnich elementow w l-tym wierszu\n2 - obliczyc srednia geometryczna dodatnich elementow w l-tej kolumnie\n3 - obliczyc srednia geometryczna dodatnich elementow lezacych na glownej przekatnej\n4 - obliczyc srednia geometryczna dodatnich elementow pod glowna przekatna\n5 - obliczyc srednia geometryczna dodatnich elementow z drugiej przekatnej\n\n");
			printf("Wybor: ");
			if (!(scanf("%d", &opcja1)))error(1, "(zle wczytana liczba)");
			if (opcja1 != 0 && opcja1 != 1 && opcja1 != 2 && opcja1 != 3 && opcja1 != 4 && opcja1 != 5)
			{
				error(1, "przy 2 wyborze");
			}
			if (opcja1 == 1 || opcja1 == 2)
			{
				printf("\n\nPodaj dla ktorej(l-tej) kolumny lub ktorego(l-tego) wiersza obliczyc srednia(od 1 i nie wiekszy niz %d)", n);
				printf("\nWybor: ");
				if (!(scanf("%d", &opcja2)))error(1, "(zle wczytana liczba)");
				if (opcja2<1 || opcja2>n)
				{
					error(1, "przy 3 wyborze");
				}
			}
			if (opcja1 == 0)
			{
				double* X;
				if (!(fz = fopen("wektor.txt", "r"))) error(2, "podczas sczytywania");
				int rozmiar = 0;
				odczytaj_wymiary_wektora(fz, &rozmiar);
				rewind(fz);
				printf("\n%d\n", rozmiar);
				X = (double*)malloc(rozmiar * sizeof(double));
				for (int i = 0; i < rozmiar; i++)//sczytanie macierzy z pliku do wektora X
				{
					if (!(fscanf(fz, "%lf", &X[i])))error(4, "(bledny znak w macierzy)");
				}
				funkcja(X, rozmiar, opcja1, opcja2);
				free(X);
				X = NULL;
				fclose(fz);
			}
			else funkcja(A, n, opcja1, opcja2);
			free(A);
			A = NULL;
			fclose(fd);
		}
		else
		{
			error(4, "(wiersze i kolumny macierzy nie sa rowne)");
		}
		return 0;
	}
	else
	{
		error(1, "przy 1 wyborze");
	}

	return 0;
}

void funkcja(double* a, int n, int opcja1, int opcja2)
{
	switch (opcja1)
	{
	case 0:
	{
		printf("srednia: %lf", srednia_geo(n, a));
		break;
	}
	case 1:
	{
		double** pom;
		pom = (double**)malloc(sizeof(double*) * n);
		for (int i = 0; i < n; i++)
		{
			pom[i] = &a[i * n];
		}

		printf("srednia: %.2lf", srednia_geo(n, pom[opcja2 - 1]));
		break;
	}
	case 2:
	{
		double* pom;
		pom = (double*)malloc(sizeof(double) * n);
		for (int i = 0; i < n; i++)
		{
			pom[i] = a[(opcja2 - 1) + i * n];
		}
		printf("srednia: %.2lf", srednia_geo(n, pom));
		break;
	}
	case 3:
	{
		double* pom;
		pom = (double*)malloc(sizeof(double) * n);
		for (int i = 0; i < n; i++)
		{
			pom[i] = a[i * n + i];
		}
		printf("srednia: %.2lf", srednia_geo(n, pom));
		break;
	}
	case 4:
	{
		double* pom;
		pom = (double*)malloc(sizeof(double) * (n * (n - 1) / 2));
		int k = 0;
		for (int i = 1; i < n; i++) //zaczynamy od 1 wierszu aby pominac 
		{
			for (int j = 0; j < i; j++)
			{
				pom[k] = a[i * n + j];
				k++;
			}
		}
		printf("srednia: %.2lf", srednia_geo(n, pom));
		break;
	}
	case 5:
	{
		double* pom;
		pom = (double*)malloc(sizeof(double) * n);
		for (int i = 0; i < n; i++)
		{
			pom[i] = a[(i + 1) * (n - 1)];
		}
		printf("srednia: %.2lf", srednia_geo(n, pom));
		break;
	}
	}
}

double srednia_geo(int nn, double* x)
{
	double wynik = 1;
	int ile = 0;
	for (int i = 0; i < nn; i++) {
		if (x[i] > 0) {
			wynik *= x[i];
			ile++;
		}
	}
	return pow(wynik, 1.0 / ile);
}

void generowanie_macierzy(FILE* fw, double** tab, int n)
{
	tab = (double**)malloc(sizeof(double*) * n);
	if (!tab)
	{
		error(3, "(alokacja 2)");
	}
	for (int i = 0; i < n; i++)
	{
		tab[i] = (double*)malloc(sizeof(double) * n);
		if (!tab[i])
		{
			error(3, "(alokacja 3)");
		}
	}
	srand(time(NULL));;
	for (int i = 0; i < n; i++) // wylosowanie liczb do macierzy[-100;100]
	{
		for (int j = 0; j < n; j++)
		{
			tab[i][j] = rand() % 201 - 100;
		}

		printf("\n");

	}
	int pokaz;
	printf("Jesli chcesz wyswietlic macierz wybierz 1\nwybor: ");
	if (!(scanf("%d", &pokaz)))error(1, "(zle wczytana liczba)");
	if (pokaz == 1)
		printf("\nWygenerowana i zapisana macierz:\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == n - 1)
			{
				if (pokaz == 1)
					printf("%.2lf", tab[i][j]);
				fprintf(fw, "%.2lf", tab[i][j]);
			}
			else
			{
				if (pokaz == 1)
					printf("%.2lf ", tab[i][j]);
				fprintf(fw, "%.2lf ", tab[i][j]);
			}
		}
		if ((i + 1) < n)
		{
			if (pokaz == 1)
				printf("\n");
			fprintf(fw, "\n");
		}
	}

}

void odczytaj_wymiary_pliku(FILE* fd, int* wiersze, int* kolumny)
{
	// wyznaczamy iloœæ wierszy i kolumn w pliku
	int ilosc_wierszy = 1, ilosc_spacji = 0, ilosc_kolumn = 1;
	int licznik = 0, licznik_2 = 0;
	char znak;
powrot:
	while ((znak = fgetc(fd)) != EOF) // wczytujemy znak po znaku, az do konca pliku
	{
		if (znak == '\n')
		{
			ilosc_wierszy++;
			licznik = 1;
			goto powrot;
		}
		if (licznik == 0)
			if (znak == ' ')ilosc_kolumn++;
		if (licznik == 1)
			if (znak == ' ')licznik_2++;
	}
	for (int i = 0; licznik_2 >= 0; i++)
	{
		licznik_2 = licznik_2 - (ilosc_kolumn - 1);
		if (licznik_2 == 0)
		{
			*wiersze = ilosc_wierszy;
			*kolumny = ilosc_kolumn;
		}
	}

}
void odczytaj_wymiary_wektora(FILE* fd, int* kolumny)
{
	// wyznaczamy iloœæ wierszy i kolumn w pliku
	int ilosc_kolumn = 1;
	char znak;
	while ((znak = fgetc(fd)) != EOF || znak == '\n') // wczytujemy znak po znaku, az do konca pliku
	{
		if (znak == ' ')ilosc_kolumn++;
	}
	*kolumny = ilosc_kolumn;
}

