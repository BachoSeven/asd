#include <iostream>
#include <cstdlib>

using namespace std;

constexpr auto dimensione=7;

void scambia(int *a, int *b)
{
	*a+=*b;
	*b=*a-*b;
	*a-=*b;
}

int partizione(int *a, int sx, int px, int dx)
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

void quickSort(int *a, int sx, int dx)
{
	if(sx<dx) {
		srand(time(NULL));
		int px=rand() % (dx-sx+1) + sx;
		int rk=partizione(a,sx,px,dx); // scelgo il pivot a caso
		quickSort(a,sx,rk-1);
		quickSort(a,rk+1,dx);
	}
}

int main()
{
	int *a=new int[dimensione];
	for(int i=0;i<dimensione;i++){
		scanf("%d",a+i);
	}
	// Chiamo la procedura di ordinamento
	quickSort(a,0,dimensione-1);
	cout << "Risultato: \n";
	for(int i=0;i<dimensione;i++){
		printf("%d ",a[i]);
	}
	cout << endl;

	delete[] a;
	return 0;
}
