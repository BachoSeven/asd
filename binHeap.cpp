#include <iostream>

using namespace std;

constexpr auto dimensione=10;

int isBinHeap(int *a)
{
	int i,k=1;
	for (i = dimensione-1; i >= 0; --i) {
		if(a[i]>a[(i-1)/2]) k=0;
	}
	return k;
}

int main()
{
	int *a=new int[dimensione];
	cout << "Inserisci un array candidato ad essere uno heap binario (max):\n";
	for(int i=0;i<dimensione;i++){
		scanf("%d",a+i);
	}

	int out=isBinHeap(a);
	cout << "risultato: " << endl << out << endl;

	delete[] a;
	return 0;
}
