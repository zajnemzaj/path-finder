/*Feltöltjük a mátrixunkat p valószínűség alapján 0 vagy 1 számokkal, és kiíratjuk*/
#include <stdio.h>
#include <math.h> // rand-hoz kell
#include <time.h> // time-hoz kell
#include <stdlib.h> // srand-hoz kell

#define MMERET 10// tábla méret
//#define p 0.3 // p valószínűség
#define ismetles 1000
#define szorasfinomsag 100

#define max(a,b) (a>b?a:b)

void matrixfeltoltes(int fmatrix[MMERET][MMERET], float fp);

void matrixkiiratas(int fmatrix[MMERET][MMERET]);

void vektorfeltoltes(int fvektor[2][MMERET*2]);

void bejaras(int fmatrix[MMERET][MMERET], int fsegedvektor[2][MMERET*2]);

void clusterjoin(int fmatrix[MMERET][MMERET], int fsegedvektor[2][MMERET*2]);

int eldont(int fmatrix[MMERET][MMERET]);

void matrixkiiratas2(int fsegedvektor[2][MMERET*2]);

int main(void) 
{
	int matrix[MMERET][MMERET], atmente;
	int segedvektor[2][MMERET*2];
	srand ( time(NULL) );
	float valosz;
	FILE *fp;
	fp = fopen("1_3.txt", "w+");
	 
	//matrixfeltoltes(matrix,p);
	//matrixkiiratas(matrix);
	for (int j = 0; j < szorasfinomsag; j++)
	{
		atmente = 0;
		float p = (float)j/szorasfinomsag;
		for (int i = 0; i < ismetles; i++)
		{
			vektorfeltoltes(segedvektor);
			matrixfeltoltes(matrix,p);
			//printf("Kezdő mátrix %.1f szórásvalószínűség mellett:\n",p);matrixkiiratas(matrix);
			bejaras(matrix,segedvektor);
			//printf("Cluster mátrix:\n");matrixkiiratas(matrix);
			clusterjoin(matrix,segedvektor);
			//printf("Clusterjoined mátrix:\n");matrixkiiratas(matrix);
			//printf("Segédvektorunk:\n");matrixkiiratas2(segedvektor);
			atmente += eldont(matrix);
			//printf("Eddig ennyi probálkozás sikerült: %d\n",atmente);
		}
		valosz = (float)atmente / (float)ismetles * 100;
		printf("Sikeres átjárások %.2f szórásvalószínűség mellett: %.2f szazalek \n",p,valosz);
		fprintf( fp, "%.2f %.2f\n", p, valosz);
	}
	
	fclose(fp);
	return 0;
}

void matrixkiiratas2(int fsegedvektor[2][MMERET*2])
{
	for (int i = 0; i < MMERET*2; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("%d ",fsegedvektor[j][i]);
		printf("\n");
	}
}

int eldont(int fmatrix[MMERET][MMERET])
{
	for (int i = 0; i < MMERET; i++)
	{
		if (fmatrix[0][i] != 0)
		{
			for (int j = 0; j < MMERET; j++)
			{
				if (fmatrix[MMERET-1][j] == fmatrix[0][i])
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void clusterjoin(int fmatrix[MMERET][MMERET], int fsegedvektor[2][MMERET*2])
{
	for (int k = 0; k < MMERET*2; k++)
		if (fsegedvektor[1][k] != 0)
			for (int i = 0; i < MMERET; i++)
				for (int j = 0; j < MMERET; j++)
					if ((fmatrix[i][j] != 0) && (fmatrix[i][j] == fsegedvektor[1][k]))
						fmatrix[i][j] = fsegedvektor[0][k];
}

void bejaras(int fmatrix[MMERET][MMERET], int fsegedvektor[2][MMERET*2])
{
	int clusterszam = 1;
	int unioszam = 0;
	for (int i=0; i < MMERET; i++)
		for (int j=0; j < MMERET; j++)
			if (fmatrix[i][j]) 
			{                        // if occupied ...
				int up = (i==0 ? 0 : fmatrix[i-1][j]);    //  look up  
				int left = (j==0 ? 0 : fmatrix[i][j-1]);  //  look left
	 
				switch (!!up + !!left)
				{
					case 0:
						fmatrix[i][j] = clusterszam++;		// a new cluster
						break;
	  
					case 1:                              	// part of an existing cluster
						fmatrix[i][j] = max(up,left);       // whichever is nonzero is labelled
						break;
	  
					case 2:     
						if (up != left)						// this site binds two clusters
							if (up < left)
							{
								fmatrix[i][j] = up;
								fsegedvektor[0][unioszam] = up;
								fsegedvektor[1][unioszam] = left;
								unioszam++;
							} 
							else
							{
								fmatrix[i][j] = left;
								fsegedvektor[0][unioszam] = left;
								fsegedvektor[1][unioszam] = up;
								unioszam++;
							}
						else
							fmatrix[i][j] = up;
						break;
				}
	
			}
}

void vektorfeltoltes(int fvektor[2][MMERET*2])
{
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < MMERET*2; i++)
		{
			fvektor[j][i] = 0;
		}
	
}

void matrixfeltoltes(int fmatrix[MMERET][MMERET], float fp)
{
	for (int i = 0; i < MMERET; i++)
	{
		for (int j = 0; j < MMERET; j++)
		{
			float irany = rand();
			float kicsirand = irany / RAND_MAX;
			if (kicsirand < fp)
			{
				fmatrix[i][j] = 1;
			} else
			{
				fmatrix[i][j] = 0;
			}
			
		}
	}
}
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GRAY    "\x1b[1;32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void matrixkiiratas(int fmatrix[MMERET][MMERET])
{
	for (int i = 0; i < MMERET; i++)
	{
		for (int j = 0; j < MMERET; j++)
		{
			switch (fmatrix[i][j])
			{
				case 1:
					printf(ANSI_COLOR_RED   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				case 2:
					printf(ANSI_COLOR_GREEN   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				case 3:
					printf(ANSI_COLOR_YELLOW   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				case 4:
					printf(ANSI_COLOR_BLUE   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				case 5:
					printf(ANSI_COLOR_MAGENTA   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				case 6:
					printf(ANSI_COLOR_CYAN   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				case 7:
					printf(ANSI_COLOR_GRAY   "%2d "  ANSI_COLOR_RESET,fmatrix[i][j]);
					break;
				default:
					printf("%2d ",fmatrix[i][j]);
					
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
