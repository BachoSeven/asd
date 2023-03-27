/*
0. generare un array di interi scelti casualmente
1. Insertion sort
2. Quicksort
*/

#include <iostream>
#include <cstdlib> // per rand
#include <sys/time.h> // per gettimeofday

using namespace std;

constexpr auto dim=8192; // 2^13
constexpr auto MAX=8192;

// procedura per l'insertion sort
void insSort(int *a, int n)
{
	for(int j=1; j<n; j++){
		int next=a[j];
		int i=j-1;
		while(i>=0 && a[i]>next){ // finchè non trovo il posto di next, "shifto" tutto a destra
			a[i+1]=a[i];
			i--;
		}
		a[i+1]=next; // uscita dal while -> piazzo next al suo posto
	}
}

// procedure per il quick sort:
void scambia(int *a, int *b) // dati due puntatori ad interi, scambia i loro valori
{
	*a+=*b;
	*b=*a-*b;
	*a-=*b;
}
int partizione(int *a, int sx, int px, int dx) // dato un pivot, divide il sottoarray in due sezioni confrontando gli elementi con esso
{
	if(px!=dx) { scambia(a+px,a+dx); }
	int i=sx;
	int j=dx-1;
	while(i<=j){
		while((i<=j) && (a[i]<=a[dx])){
			i++;
		}
		while((i<=j) && (a[j]>=a[dx])){
			j--;
		}
		if(i<j) { scambia(a+i,a+j); }
	}
	if(i!=dx) { scambia(a+i,a+dx); }
    return i;
}
void quickSort(int *a, int sx, int dx) // procedura principale
{
	if(sx<dx) {
		int px=rand() % (dx-sx+1) + sx; // scelgo il pivot in modo pseudorandom
		int rk=partizione(a,sx,px,dx);
		quickSort(a,sx,rk-1);
		quickSort(a,rk+1,dx);
		}
}

int main()
{
	// alloca lo spazio per l'array
	int *a=new int[dim];

	// inizializza il seed per rand qui, per tutto il main
	srand(time(NULL));

	// crea un array di numeri pseudorandom
	for (int i=0; i<dim; i++){
		a[i]=rand() % MAX;
	}

	// Parsing delle "opzioni"
	char tmp;
	cout << "\nOpzioni disponibili: quick sort, insertion sort, benchmark dei tempi di esecuzione.\nCosa vuoi fare? [Q|I|B]? ";
	cin >> tmp;
	int ans=(int)tmp;
	cout << endl;

	if(ans == 73){ // I
		insSort(a,dim);
		// Stampa l'array ordinato tramite insSort
		cout << "Array ordinato tramite l'insertion sort:" << endl << endl;
		for(int i=0;i<dim;i++){
			printf("%d ",*(a+i));
		}
		cout << endl;
	} else if(ans == 81){ // Q
		quickSort(a,0,dim-1);
		// Stampa l'array ordinato tramite quickSort
		cout << "Array ordinato tramite il quick sort:" << endl << endl;
		for(int i=0;i<dim;i++){
			printf("%d ",*(a+i));
		}
		cout << endl;
	} else if(ans == 66){ // Misuriamo i tempi di esecuzione degli algoritmi (senza stampare gli array)
		// Faccio una copia temporanea dell'array
		int *b=new int[dim];
		for(int i=0; i<dim; i++){
			b[i]=a[i];
		}

		struct timeval beg, end;

		gettimeofday(&beg, NULL);
		insSort(a,dim);
		gettimeofday(&end, NULL);
		cout << "Insertion Sort: " << "\n\t" << ((end.tv_sec - beg.tv_sec)*1000000 + end.tv_usec - beg.tv_usec) << "us" << endl;

		gettimeofday(&beg, NULL);
		quickSort(b,0,dim-1);
		gettimeofday(&end, NULL);
		cout << "Quick Sort: " << "\n\t" << ((end.tv_sec - beg.tv_sec)*1000000 + end.tv_usec - beg.tv_usec) << "us" << endl;

		delete[] b;
	}

	delete[] a;
	return 0;
}
