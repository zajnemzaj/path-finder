/*Feltöltjük a mátrixunkat p valószínűség alapján 0 vagy 1 számokkal, és kiíratjuk*/
#include <stdio.h>
#include <math.h> // rand-hoz kell
#include <time.h> // time-hoz kell
#include <stdlib.h> // srand-hoz kell

#define MMERET 10// tábla méret
//#define p 0.3 // p valószínűség
#define ismetles 100

void matrixfeltoltes(int fmatrix[MMERET][MMERET], float fp);

void matrixkiiratas(int fmatrix[MMERET][MMERET]);

int bejaras(int fmatrix[MMERET][MMERET]);

int main(void) 
{
	int matrix[MMERET][MMERET], atmente;
	srand ( time(NULL) );
	float seged, valosz;
	FILE *fp;
	fp = fopen("1_3.txt", "w+");
	 
	//matrixfeltoltes(matrix,p);
	//matrixkiiratas(matrix);
	for (float j = 0; j < 10; j++)
	{
		atmente = 0;
		float p = j/10;
	
	
	
		for (int i = 0; i < ismetles; i++)
		{
			matrixfeltoltes(matrix,p);
			atmente += bejaras(matrix);
		}
		seged = atmente;
		valosz = seged / ismetles * 100;
		printf("Sikeres átjárások %.1f szórásvalószínűség mellett: %.2f szazalek \n",p,valosz);
		fprintf( fp, "%.2f %.2f\n", p, valosz);
	}
	fclose(fp);
}

int max(int fup, int fleft)
{
	if (fup != 0)
		return fup;
	else
		if (fleft != 0)
			return fleft;
	return 0;
}

int bejaras(int fmatrix[MMERET][MMERET])
{
	for (int i=0; i<MMERET; i++)
		for (int j=0; j<MMERET; j++)
			if (fmatrix[i][j]) 
			{                        // if occupied ...
				int up = (i==0 ? 0 : fmatrix[i-1][j]);    //  look up  
				int left = (j==0 ? 0 : fmatrix[i][j-1]);  //  look left
	
				switch (!!up + !!left)
				{
					case 0:
						fmatrix[i][j] = uf_make_set();      // a new cluster
						break;
	  
					case 1:                              	// part of an existing cluster
						fmatrix[i][j] = max(up,left);       // whichever is nonzero is labelled
						break;
	  
					case 2:                              	// this site binds two clusters
						fmatrix[i][j] = uf_union(up, left);
						break;
				}
	
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

void matrixkiiratas(int fmatrix[MMERET][MMERET])
{
	for (int i = 0; i < MMERET; i++)
	{
		for (int j = 0; j < MMERET; j++)
		{
			printf("%d ",fmatrix[i][j]);
		}
		printf("\n");
	}
}
