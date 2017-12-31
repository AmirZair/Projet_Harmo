#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tri_a_bulle(int *tab, int taille) {
	int j, k, tmp;
	for(;taille>1;taille=k) {
		for(k=j = 0 ; j < taille-1 ; j++) {
			if(tab[j] > tab[j+1]) {
				tmp = tab[j];
				tab[j] = tab[j+1];
				tab[k=j+1]=tmp; //Prise de la case la plus haute pour l'échange
			}
		}
	}
}

void tri_selection(int *tab, int taille){
	int i, imin, j, tmp;
	for(i=0; i<taille; i++){
		imin=i;
		for(j=i+1; j<taille; j++){
			if(tab[j]<tab[imin]){
				imin=j;
			}
		}
		tmp=tab[i];
		tab[i]=tab[imin];
		tab[imin]=tmp;
	}
}


void tri_selection_double(double *tab, int taille){
	int i, imin, j;
	double tmp;
	for(i=0; i<taille; i++){
		imin=i;
		for(j=i+1; j<taille; j++){
			if(tab[j]<tab[imin]){
				imin=j;
			}
		}
		tmp=tab[i];
		tab[i]=tab[imin];
		tab[imin]=tmp;
	}
}

void tri_insertion(int *tab, int taille) {
	int i, j, tmp;
	for(i = 0;i<taille;i++) {
		tmp = tab[i];
		j=i;
		while(j>0 && tab[j-1]>tmp) {
			tab[j]=tab[j-1];
			j--;
		}
		tab[j]=tmp;
	}
}

int *remplir_aleatoirement_int(int n) {
	int *t = malloc(n*sizeof(*t));
	int i;
	for(i=0;i<n;i++) {
		t[i]=rand()%(3*n);
	}
	return t;
}



double tri_selection_mesure(int taille, int *tab) {
	clock_t a = clock();
	//printf("a = %f\n",a);
	tri_selection(tab,taille);
	//printf("¨fin : %.6f\n",clock());
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

void selection_recursif(int *tab, int taille){
	if(taille<2) return;
	int imin=0, j;
	for(j=1; j<taille; j++){
		if(tab[j]<tab[imin]){
			imin=j;
		}
	}
	int x = tab[imin]; tab[imin]=*tab; *tab=x;
	selection_recursif(tab+1, taille-1);
}

double selection_recursif_mesure(int taille, int *tab) {
	clock_t start_t;
	start_t = clock();
	selection_recursif(tab,taille);

	return (clock()-start_t+0.)/CLOCKS_PER_SEC;
}

double moyenne_tri_selection(int n) {
	int i,*t;
	double cumul=0;
	for(i=0;i<20;i++) {
		t = remplir_aleatoirement_int(n);
		cumul = cumul + tri_selection_mesure(n, t);
		printf("%.5f\n", tri_selection_mesure(n,t));
		//if(i<20) printf(" | ");
		free(t);
	}
	return (cumul + 0.)/20;
}

double tri_bulle_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_a_bulle(tab,n);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

double tri_insertion_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_insertion(tab,n);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

int partition(int *tab, int debut, int fin, int indice_pivot)
{
	int p=tab[indice_pivot],i,j;
	tab[indice_pivot]=tab[fin];
	for (i=j=debut; i <= fin-1; i++)
	{
		if(tab[i]<p)
		{
			int x=tab[i]; tab[i]=tab[j]; tab[j++]=x;
		}
		//tab[debut ..j-1] contient les petits nombres
		//tab[j..fin-1] contient les grands nombrs
	}
	tab[fin]=tab[j];
	tab[j]=p;
	return j;
}

void tri_rapide(int *tab,int debut, int pivot, int fin)
{
	if(fin>debut){
	int j=partition(tab,debut,fin,pivot);
	tri_rapide(tab,debut,(j+debut)/2,j);
	tri_rapide(tab,j+1,(j+fin)/2,fin);}
}

double tri_rapide_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_rapide(tab,0,n/2,n);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

void compare_tris(int taille) {
	int *t, u[taille], v[taille], i, faux;
	t=remplir_aleatoirement_int(taille);
	for(i=0;i<taille;i++) u[i]=v[i]=t[i];
	printf("Tri par sélection de %d entiers : %.2f\n",taille,tri_selection_mesure(taille,u));
	printf("Tri par insertion de %d entiers : %.2f\n",taille,tri_insertion_mesure(taille,v));
	for(faux=i=0;i<taille;i++) faux|=u[i]-v[i], u[i]=t[i];
	if(faux) printf("faux\n");
	printf("Tri à bulle de %d entiers : %.2f\n",taille,tri_bulle_mesure(taille,u));
	for(faux=i=0;i<taille;i++) faux|=u[i]-v[i], u[i]=t[i];
	if(faux) printf("faux\n");
	printf("Tri rapide de %d entiers : %.2f\n",taille,tri_rapide_mesure(taille,u));
	for(faux=i=0;i<taille;i++) faux|=u[i]-v[i], u[i]=t[i];
	if(faux) printf("faux\n");
	free(t);
}

int main()
{
	compare_tris(10000);
    return 0;
}
