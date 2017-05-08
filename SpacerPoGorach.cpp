#include <stdio.h>
#include <stdlib.h>

#define INF 10000000

struct point{
	int x;
	int y;
};

struct punkt_do_kol{
	point A;
	int w;
};

struct heap{
	punkt_do_kol* body;
	int size;
	int max_size;
};

struct wyciag{
	point to;
	int time;
	int starts;
};

struct punkt{
	int hight;
	wyciag* wyciagi;
	int l_wyciagow;
	int w;
	bool odw;
};

int heap_push(heap &h, punkt_do_kol e){
	if (h.size+1 == h.max_size){
		h.max_size *= 2;
		h.body = (punkt_do_kol*)realloc(h.body, h.max_size* sizeof(punkt_do_kol));
	}
	int i;
	punkt_do_kol tmp;
	h.size++;
	h.body[h.size] = e;
	i = h.size;
	while (i != 1){
		if (h.body[i].w < h.body[i / 2].w){
			tmp = h.body[i];
			h.body[i] = h.body[i / 2];
			h.body[i / 2] = tmp;
			i /= 2;
		}
		else
			break;
	}
	return 0;
}

int heap_pop(heap &h){
	if (h.size == 0)
		return -1;
	int i = 1;
	punkt_do_kol tmp;
	h.body[1] = h.body[h.size];
	h.size--;
	while (h.size >= 2 * i){
		if (h.size < 2 * i + 1){
			if (h.body[i].w>h.body[2 * i].w){
				tmp = h.body[i];
				h.body[i] = h.body[2 * i];
				h.body[2 * i] = tmp;
				i *= 2;
				continue;
			}
			else
				break;
		}
		if (h.body[2 * i].w < h.body[i].w || h.body[2 * i + 1].w < h.body[i].w){
			if (h.body[2 * i].w < h.body[2 * i + 1].w){
				tmp = h.body[2 * i];
				h.body[2 * i] = h.body[i];
				h.body[i] = tmp;
				i *= 2;
			}
			else{
				tmp = h.body[2 * i + 1];
				h.body[2 * i + 1] = h.body[i];
				h.body[i] = tmp;
				i = 2 * i + 1;
			}
		}
		else
			break;
	}
	return 0;
}

punkt_do_kol heap_top(heap &h){
	return h.body[1];
}

int min(int a, int b){
	if (a < b)
		return a;
	else
		return b;
}

int odl(punkt a, punkt b){
	if (a.hight >= b.hight)
		return 1;
	else
		return b.hight - a.hight + 1;
}

int main(){
	int X, Y, w, starts, time;
	point start, end, A;
	wyciag W;
	heap dijkstra;
	dijkstra.size = 0;
	punkt_do_kol P, Q;
	int i, j, k;

	scanf("%d%d", &Y, &X);
	punkt** mapa;
	mapa = (punkt**)malloc(sizeof(punkt*)*X);
	for (i = 0; i < X; i++)
		mapa[i] = (punkt*)malloc(sizeof(punkt)*Y);
	scanf("%d%d", &start.y, &start.x);
	scanf("%d%d", &end.y, &end.x);
	scanf("%d", &w);
	dijkstra.max_size = 100;
	dijkstra.body = (punkt_do_kol*)malloc(sizeof(punkt_do_kol)*dijkstra.max_size);
	for (i = 0; i < X; i++)
	for (j = 0; j < Y; j++){
		mapa[i][j].l_wyciagow = 0;
		mapa[i][j].w = INF;
		mapa[i][j].odw = false;
	}
	for (i = 0; i < w; i++){
		scanf("%d%d", &A.y, &A.x);
		scanf("%d%d%d%d", &W.to.y, &W.to.x, &W.time, &W.starts);
		if (mapa[A.x][A.y].l_wyciagow == 0)
			mapa[A.x][A.y].wyciagi = (wyciag*)malloc(sizeof(wyciag));
		else
			mapa[A.x][A.y].wyciagi = (wyciag*)realloc(mapa[A.x][A.y].wyciagi, sizeof(wyciag)*(mapa[A.x][A.y].l_wyciagow + 1));
		mapa[A.x][A.y].wyciagi[mapa[A.x][A.y].l_wyciagow] = W;
		mapa[A.x][A.y].l_wyciagow++;
	}
	for (i = 0; i < X; i++)
	for (j = 0; j < Y; j++){
		scanf("%d", &mapa[i][j].hight);
	}

	mapa[start.x][start.y].w = 0;
	P.A = start;
	P.w = 0;
	heap_push(dijkstra, P);
	while (dijkstra.size){
		P = heap_top(dijkstra);
		heap_pop(dijkstra);
		if (mapa[P.A.x][P.A.y].odw == true)
			continue;
		mapa[P.A.x][P.A.y].odw = true;
		if (P.A.x == end.x && P.A.y == end.y)
			break;
		if (P.A.x + 1 < X && mapa[P.A.x + 1][P.A.y].odw == false){
			Q.A.x = P.A.x + 1;
			Q.A.y = P.A.y;
			Q.w = mapa[Q.A.x][Q.A.y].w = min(mapa[Q.A.x][Q.A.y].w, mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]));
			if (Q.w == mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]))
				heap_push(dijkstra, Q);
		}
		if (P.A.y + 1 < Y && mapa[P.A.x][P.A.y + 1].odw == false){
			Q.A.x = P.A.x;
			Q.A.y = P.A.y + 1;
			Q.w = mapa[Q.A.x][Q.A.y].w = min(mapa[Q.A.x][Q.A.y].w, mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]));
			if (Q.w == mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]))
				heap_push(dijkstra, Q);
		}
		if (P.A.x - 1 >= 0 && mapa[P.A.x - 1][P.A.y].odw == false){
			Q.A.x = P.A.x - 1;
			Q.A.y = P.A.y;
			Q.w = mapa[Q.A.x][Q.A.y].w = min(mapa[Q.A.x][Q.A.y].w, mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]));
			if (Q.w == mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]))
				heap_push(dijkstra, Q);
		}
		if (P.A.y - 1 >= 0 && mapa[P.A.x][P.A.y - 1].odw == false){
			Q.A.x = P.A.x;
			Q.A.y = P.A.y - 1;
			Q.w = mapa[Q.A.x][Q.A.y].w = min(mapa[Q.A.x][Q.A.y].w, mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]));
			if (Q.w == mapa[P.A.x][P.A.y].w + odl(mapa[P.A.x][P.A.y], mapa[Q.A.x][Q.A.y]))
				heap_push(dijkstra, Q);
		}
		for (j = 0; j < mapa[P.A.x][P.A.y].l_wyciagow; j++){
			Q.A.x = mapa[P.A.x][P.A.y].wyciagi[j].to.x;
			Q.A.y = mapa[P.A.x][P.A.y].wyciagi[j].to.y;
			time = mapa[P.A.x][P.A.y].wyciagi[j].time;
			starts = mapa[P.A.x][P.A.y].wyciagi[j].starts;
			if (mapa[Q.A.x][Q.A.y].odw == false){
				Q.w = mapa[Q.A.x][Q.A.y].w = min(mapa[Q.A.x][Q.A.y].w, mapa[P.A.x][P.A.y].w + time + (starts - mapa[P.A.x][P.A.y].w%starts) % starts);
				if (Q.w == mapa[P.A.x][P.A.y].w + time + (starts - mapa[P.A.x][P.A.y].w%starts) % starts)
					heap_push(dijkstra, Q);
			}
		}
	}

	printf("%d\n", mapa[end.x][end.y].w);

	free(dijkstra.body);
	for(i=0; i<X; i++){
		for(j=0; j<Y; j++)
			if(mapa[i][j].l_wyciagow)
				free(mapa[i][j].wyciagi);
		free(mapa[i]);
	}
	free(mapa);

	return 0;
}
