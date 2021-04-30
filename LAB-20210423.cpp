/*

  Costruire un albero binario di ricerca a partire da un vettore ordinato senza ripetizioni.
  Fare la visita simmetrica dell'albero.

*/

/* Costruire un vettore random ordinato senza ripetizioni  */

/* Costruire un albero binario di ricerca e farne la visita simmetrica */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm> // sort() per vector

using namespace std;

constexpr int DIM=100;
constexpr int MAX= 1000;

typedef struct bN{
	int chiave;
	struct bN* left;
	struct bN* right;
} Node;

typedef Node *bT;

bT BST(vector<int> v,int l,int r){
	if (l>r) return NULL;
	int n=(l+r)/2;
	bT tmp=new Node;
	tmp->chiave=v[n];
	tmp->left=BST(v,l,n-1);
	tmp->right=BST(v,n+1,r-1);
	return tmp;
}

void printBST(bT B){
	if (B!=NULL) {
		printBST(B->left);
		cout << B->chiave << " ";
		printBST(B->right);
	}
}

void delBST(bT b){
	if (b!=NULL) {
		delBST(b->left);
		delBST(b->right);
		delete[] b;
	}
}

int main() {
	/*
	Vettore random:
	 - ordinare
	 - rimuovere i duplicati
	*/
	srand(time(NULL));
	vector<int> v;
	for (int i=0; i<DIM; i++){
		v.push_back(rand() % MAX);
	}
	sort(v.begin(),v.end());
	int j=0;
	for(int i =j+1; i<v.size();i++){
		if(v[i]!=v[j]){
			j++;
			v[j]=v[i];
		}
	}
	v.erase(v.begin()+j+1, v.end()); // rimuove gli elementi vuoti

	// Creare il BST usando il fatto che il vettore è ordinato, allocando ogni volta la radice(=elemento centrale)
	bT B=BST(v,0,v.size()-1);

	// Visita simmetrica per verificare che il BST sia ordinato
	printBST(B);
	cout << endl;

	// Visita posticipata per deallocare l'albero
	delBST(B);
}
