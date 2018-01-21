#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tri_bulle(int *tab, int taille) {
	int  tmp,i,j;
  	 for (i = 0; i < taille-1; i++)      
       for (j = 0; j < taille-i-1; j++) 
           if (tab[j] > tab[j+1])
              {
              	tmp = tab[j];
              	tab[j] = tab[j+1];
              	tab[j+1] = tmp;
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

void tri_selection_recursif(int *tab, int taille){
	if(taille<2) return;
	int imin=0, j;
	for(j=1; j<taille; j++){
		if(tab[j]<tab[imin]){
			imin=j;
		}
	}
	int x = tab[imin]; tab[imin]=*tab; *tab=x;
	tri_selection_recursif(tab+1, taille-1);
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

void tri_cocktail( int *tab, int taille)
{
    int i, j, tmp;
    int stop;
    i = 0;
    do{
	    stop = 1;
	    for(j=0; j<taille-i-1; j++)
	    {
		if( tab[j] > tab[j+1])
		{
			tmp = tab[j+1];
			tab[j+1] = tab[j];
			tab[j] = tmp;

			stop = 0;
		}
	    }
	    if(stop == 1)
		break;

	    stop = 1;

	    for(j=taille-2-i; j>i; j--)
	    {
		if( tab[j-1] > tab[j])
		{
			tmp = tab[j];
			tab[j] = tab[j-1];
			tab[j-1] = tmp;
		    stop = 0;
		}
	    }
	    if(stop==1)
	    	break;
	    else
	    	stop=1;
    }while(stop);
}


void tri_gnome(int *tab,int taille)
{
	int i=0,temp;
	while (i<taille)
	{
		if (i==0 || tab[i]>=tab[i-1])
		{
			i=i+1;
		}
		else{
			temp=tab[i];
			tab[i]=tab[i-1];
			tab[i-1]=temp;
			i=i-1;
		}
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


double selection_recursif_mesure(int taille, int *tab) {
	clock_t start_t;
	start_t = clock();
	tri_selection_recursif(tab,taille);

	return (clock()-start_t+0.)/CLOCKS_PER_SEC;
}


double tri_bulle_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_bulle(tab,n);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

double tri_insertion_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_insertion(tab,n);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
int choose_pivot(int i,int j )
{
    return((i+j) /2);
}
 
void quicksort(int list[],int m,int n)
{
    int key,i,j,k;
    if( m < n)
    {
        k = choose_pivot(m,n);
        swap(&list[m],&list[k]);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if( i < j)
                swap(&list[i],&list[j]);
        }
        /* swap two elements */
        swap(&list[m],&list[j]);
 
        /* recursively sort the lesser list */
        quicksort(list,m,j-1);
        quicksort(list,j+1,n);
    }
}

double tri_rapide_mesure(int n, int *tab) {
	clock_t a = clock();
	quicksort(tab,0,n-1);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

double tri_cocktail_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_cocktail(tab,n);
	return (clock()-a+0.)/CLOCKS_PER_SEC;
}

double tri_gnome_mesure(int n, int *tab) {
	clock_t a = clock();
	tri_gnome(tab,n);
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
	printf("Tri cocktail de %d entiers : %.2f\n",taille,tri_cocktail_mesure(taille,u));
	for(faux=i=0;i<taille;i++) faux|=u[i]-v[i], u[i]=t[i];
	if(faux) printf("faux\n");
	printf("Tri gnome de %d entiers : %.2f\n",taille,tri_gnome_mesure(taille,u));
	for(faux=i=0;i<taille;i++) faux|=u[i]-v[i], u[i]=t[i];
	if(faux) printf("faux\n");
	printf("Tri rapide de %d entiers : %.2f\n",taille,tri_rapide_mesure(taille,u));
	for(faux=i=0;i<taille;i++) faux|=u[i]-v[i], u[i]=t[i];
	if(faux) printf("faux\n");
	free(t);
}

int main(int argc, char *argv[]) {
    
    compare_tris(200000);
    return 0;
}
