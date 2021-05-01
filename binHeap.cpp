// TODO

#include <iostream>

using namespace std;

constexpr auto dimensione=5;

int isBinHeap(int *a)
{
	return ();
}

int main()
{
	int *a=new int[dimensione];
	cout << "Inserisci un array candidato ad essere uno heap binario:\n";
	for(int i=0;i<dimensione;i++){
		scanf("%d",a+i);
	}

	isBinHeap(a);

	delete[] a;
	return 0;
}
