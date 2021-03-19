#include <iostream>
#include <vector> // per usare vector (duh)
#include <cstdlib> // per usare rand (ed srand)

/* modulo utile con alcune funzioni standard */
using namespace std;

/*
 In C sarebbe:
	#define CONSTANT 5
 Questo funziona, ma in C++:
	constexpr int CONSTANT = 5;
*/

constexpr auto dimensione=5; // Deduce il tipo automaticamente
constexpr auto MAX_RANGE = 100;

// Funzione ausiliaria
int insSort(int *a, int n)
{
	int dimensione=n;
	for(int j=1;j<dimensione;j++){
		int next=*(a+j);
		int i=j-1;
		while(i>=0&&*(a+i)>next){ // finchè non trovo il posto(<-> il primo più piccolo) di next, shifto tutto di una posizione a destra
			*(a+i+1)=*(a+i);
			i=i-1;
		}
		*(a+i+1)=next; // fine del while <-> trovato!
	}
	return 0;
}

int main()
{
/*
	// Stampa su schermo:
	Senza "using namespace std" servirebbe:
	std::cout << "Hello World!\n";

	// Così, invece:
	cout << "Ciao mondo!\n";
	// Oppure:
	cout << "Un altro ciao mondo..." << endl;

	// Input da tastiera:
	int x;
	cin >> x;
	cout << "valore di x: " << x << endl;
*/

/*
	// Generiamo un array di valori pseudorandom:
	int dim;
	string messaggio="immetti dimensione: ";

	cout << messaggio;
	cin >> dim;

	int *a=new int[dim]; // new in C

	srand(time(NULL));

	for (int i=0; i<dim; i++) {
		int x=rand() % MAX_RANGE;
		a[i]=x;
	}

// Va bene, ma il ciclo sotto è più compatto di questo
	for (int i=0; i<dim; i++){
		cout << a[i] << endl;
	}

	// per ogni x in a (stile python) [non va con l'array generato con new, ma altrimenti sì, e va con i vettori]
	// for (auto x:a){
	//	cout << x << endl;
	// }

	delete[] a; // free in C

// Vector (array dinamico)
	vector<int> A; // vuoto
	int y=5;
	A.push_back(y); // aggiunge y in fondo, divenda di dimensione 1
*/

	// Array per l'insertion sort
	int *b=new int[dimensione];
	for(int i=0;i<dimensione;i++){
		scanf("%d",b+i);
	}
	// Chiamo la procedura di ordinamento
	insSort(b,dimensione);
	for(int i=0;i<dimensione;i++){
		printf("%d\n",*(b+i));
	}

	delete[] b;
	return 0; // oki
}
