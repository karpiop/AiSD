#include<stdio.h>
#include <stdlib.h>

struct node{
	int v;
	node** children;
};

int P(node* root, int n, int k){
	int i;
	if (root != NULL){
		printf("%d ", (*root).v);
		for (i = 0; i < n; i++)
			P((*root).children[i], k, k);
	}
	return 0;
}

node* I(node* root, int n, int k, int x){
	int i, a, r;
	node* currnode;
	if (root == NULL){
		root = (node*)malloc(sizeof(node));
		(*root).v = x;
		(*root).children = (node**)malloc(n*sizeof(node*));
		for (i = 0; i < n; i++)
			(*root).children[i] = NULL;
		return root;
	}
	if ((*root).v == x){
		printf("%d exist", x);
		return root;
	}
	a = x;
	r = a%n;
	a /= n;
	currnode = root;
	while ((*currnode).children[r] != NULL){
		if ((*(*currnode).children[r]).v == x){
			printf("%d exist\n", x);
			return root;
		}
		currnode = (*currnode).children[r];
		r = a%k;
		a /= k;
	}
	(*currnode).children[r] = (node*)malloc(sizeof(node));
	(*(*currnode).children[r]).v = x;
	(*(*currnode).children[r]).children = (node**)malloc(k*sizeof(node*));
	for (i = 0; i < k; i++)
		(*(*currnode).children[r]).children[i] = NULL;
	return root;
}

int L(node* root, int n, int k, int x){
	int i, a, r;
	if (root == NULL){
		printf("%d not exist\n", x);
		return 0;
	}
	a = x / n;
	r = x%n;
	while (root != NULL){
		if ((*root).v == x){
			printf("%d exist\n", x);
			return 0;
		}
		root = (*root).children[r];
		r = a%k;
		a /= k;
	}
	printf("%d not exist\n", x);
	return 0;
}

node* D(node* root, int n, int k, int x){
	int i, a, r, candidate;
	node *parent, *tobedeleted;
	bool t;
	parent = tobedeleted = NULL;
	r = x%n;
	a = x / n;
	if (root == NULL){
		printf("%d not exist\n", x);
		return root;
	}
	if ((*root).v == x){
		candidate = -1;
		for (i = 0; i < n; i++)
		if ((*root).children[i] != NULL){
			parent = root;
			candidate = i;
			break;
		}
		if (candidate == -1){
			free(root);
			root = NULL;
			return root;
		}
		while ((*parent).children[candidate] != NULL){
			t = false;
			for (i = 0; i < k; i++)
			if ((*(*parent).children[candidate]).children[i] != NULL){
				t = true;
				parent = (*parent).children[candidate];
				candidate = i;
				break;
			}
			if (!t){
				(*root).v = (*(*parent).children[candidate]).v;
				free((*parent).children[candidate]);
				(*parent).children[candidate] = NULL;
				return root;
			}
		}
	}
	tobedeleted = root;
	while ((*tobedeleted).children[r] != NULL){
		if ((*(*tobedeleted).children[r]).v == x){
			parent = tobedeleted;
			candidate = -1;
			for (i = 0; i < k; i++)
			if ((*(*tobedeleted).children[r]).children[i] != NULL){
				parent = (*tobedeleted).children[r];
				candidate = i;
				break;
			}
			if (candidate == -1){
				free((*tobedeleted).children[r]);
				(*tobedeleted).children[r] = NULL;
				return root;
			}
			while ((*parent).children[candidate] != NULL){
				t = false;
				for (i = 0; i < k; i++)
				if ((*(*parent).children[candidate]).children[i] != NULL){
					t = true;
					parent = (*parent).children[candidate];
					candidate = i;
					break;
				}
				if (!t){
					(*(*tobedeleted).children[r]).v = (*(*parent).children[candidate]).v;
					free((*parent).children[candidate]);
					(*parent).children[candidate] = NULL;
					return root;
				}
			}
		}
		tobedeleted = (*tobedeleted).children[r];
		r = a%k;
		a /= k;
	}
	printf("%d not exist\n",x);
	return root;
}

node* F(node* root, int n, int k){
	int i;
	if (root == NULL){
		return NULL;
	}
	for (i = 0; i < n; i++){
		(*root).children[i]=F((*root).children[i], k, k);
	}
	free(root);
	return NULL;
}

int main(){
	char c;
	int x, n, k, m, i, min, max;
	node* root = NULL;

	scanf("%d\n", &m);
	scanf("%d %d\n", &min, &max);
	scanf("%d %d\n", &n, &k);

	for (i = 0; i < m; i++){
		scanf("\n%c", &c);
		switch (c)
		{
		case 'I':{
					 scanf(" %d", &x);
					 root = I(root, n, k, x);
					 break;
		}
		case 'P':{
					 P(root, n, k);
					 printf("\n");
					 break;
		}
		case 'L':{
					 scanf(" %d", &x);
					 L(root, n, k, x);
					 break;
		}
		case 'D':{
					 scanf(" %d", &x);
					 root = D(root, n, k, x);
					 break;
		}
		default:
			break;
		}
	}
	root = F(root, n, k);
	return 0;
}