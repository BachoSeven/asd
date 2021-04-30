#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int DIM=100;
constexpr int MAX= 1000;

typedef struct bN{
	int key;
	struct bN* left;
	struct bN* right;
} Node;

typedef Node *bT;

bT BST(vector<int> v,int l,int r)
{
	if (l>r) return NULL;
	int n=(l+r)/2;
	bT tmp=new Node;
	tmp->key=v[n];
	tmp->left=BST(v,l,n-1);
	tmp->right=BST(v,n+1,r-1);
	return tmp;
}

void printBST(bT B)
{
	if (B!=NULL) {
		printBST(B->left);
		cout << B->key << " ";
		printBST(B->right);
	}
}

void delBST(bT b)
{
	if (b!=NULL) {
		delBST(b->left);
		delBST(b->right);
		delete[] b;
	}
}


/* find */

int find(bT b, int v)
{
	if(b == NULL) return 0;
	if(b->key == v) return 1;
	if(b->key>v) return find(b->left,v);
	return find(b->right,v);
}

/* list */

/*

  Dati n1, n2 interi, stampare tutti i
  valori dell'albero in [n1,n2].

*/

void list(bT b, int n1, int n2)
{
	// if(b == NULL) return 0;
	// if(b->key == v) return 1;
	// if(b->key>v) return find(b->left,v);
	// return find(b->right,v);
}

int main()
{
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

	cout << "numero di operazioni: ";
	int o, n1, n2;
	char op;
	cin >> o;

	for(int i=0; i<o; i++){
		cout << "operazione " << i+1 << ": ";
		cin >> op >> n1;

		if(op == 'f'){
			printf("%d\n", find(B,n1));
		} else if(op == 'l'){
			cin >> n2;
			cout << "list: ";
			list(B,n1,n2);
			cout << endl;
		}
	}

	// Visita posticipata per deallocare l'albero
	delBST(B);
	return 0;
}
