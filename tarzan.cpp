#include <stdio.h>
#include <math.h>

#define X 100
#define INF 999999

double matrix[X][X];
int cykl[X];

typedef struct{
	int	x;
	int y;
}Punkt;

int wypisz_permutacje(int beg, int end, double min){
	int i;
	int tmp;
	double d;
	d = 0;
	for (i = 0; i < beg; i++){
		d += matrix[cykl[i- 1]][cykl[i]];
	}
	if (d >= min)
		return min;
	for (i = beg; i < end; i++){
		tmp = cykl[i];
		cykl[i] = cykl[beg];
		cykl[beg] = tmp;
		min=wypisz_permutacje(beg + 1, end, min);
		tmp = cykl[i];
		cykl[i] = cykl[beg];
		cykl[beg] = tmp;
	}
	if (beg + 1 == end){
		d = 0;
		for (i = 1; i < end; i++)
			d += matrix[cykl[i- 1]][cykl[i]];
		d += matrix[cykl[end - 1]][cykl[0]];
		if (d<min)
			return d;
	}
	return min;
}

int main() {
	int t, i, j, k, n;
	Punkt las[X];
	double d;
	char c;

	scanf("%d", &t);
	for (k = 0; k < t; k++){
		scanf("%d (", &n);
		for (i = 0; i < n; i++){
			scanf("(%d,%d)%c", &las[i].x, &las[i].y, &c);
			for (j = 0; j < i; j++)
				if (las[i].x == las[j].x && las[i].y == las[j].y){
					i--;
					n--;
					break;
				}
		}

		for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				if (i == j){
					matrix[i][j] = 0;
					continue;
				}
				if (las[i].y == las[j].y)
					matrix[i][j] = abs(las[i].x - las[j].x);
				else {
					d = sqrt((double)((las[i].x - las[j].x)*(las[i].x - las[j].x) + (las[i].y - las[j].y)*(las[i].y - las[j].y)));
					if (d < 1000)
						matrix[i][j] = d;
					else
						matrix[i][j] = abs(las[i].y - las[j].y) + abs(las[i].x) + abs(las[j].x);
				}
			}
		}
		d = INF;
		for (i = 0; i < n; i++)
			cykl[i] = i;
		d = wypisz_permutacje(0,n,d);
		printf("%d\n", (int)d);
	}
	return 0;
}