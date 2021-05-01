#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int DIM=10;
constexpr int MAX=100;

typedef struct bN{
	int key;
	int size; // #{nodi dell'albero, compresa la chiave}
	struct bN* sx;
	struct bN* dx;
} Node;

typedef Node *bT;

bT buildBST(vector<int> v,int l,int r)
{
	if (l>r) return NULL;
	int n=(l+r)/2;
	bT aux=new Node;
	aux->key=v[n];
	aux->size=r-l+1;
	aux->sx=buildBST(v,l,n-1);
	aux->dx=buildBST(v,n+1,r);
	return aux;
}

void printBSTrec(bT B)
{
	if (B != NULL) {
		printBSTrec(B->sx);
		cout << B->key << " ";
		cout << B->size << endl;
		printBSTrec(B->dx);
	}
}

void printBST(bT B) // semplice "wrapper" per estetica
{
	cout << "Array: \n";
	printBSTrec(B);
	cout << endl;
}

bT delBST(bT b)
{
	if (b != NULL) {
		// elimino i figli...
		b->sx=delBST(b->sx);
		b->dx=delBST(b->dx);
		// e poi il padre.
		delete b;
	}
	return NULL;
}

/* member */

bool member(bT b, int v)
{
	bool k=false;
	if(b != NULL){
		if(b->key==v) {
			k=true;
		} else if(b->key>v){
			k=member(b->sx,v);
		} else {
			k=member(b->dx,v);
		}
	}
	return k;
}

/* list */

/*

  Dati n1, n2 interi, stampare tutti i
  valori dell'albero in [n1,n2].

*/

void list(bT b, int n1, int n2)
{
	if(b != NULL && n1<=n2){ // necessario(probabilmente) visto che incremento gli estremi nell'ultima else-clause
		if(b->key>n2){
			list(b->sx,n1,n2);
		} else if(b->key<n1){
			list(b->dx,n1,n2);
		} else { // OSS: questo accade una sola volta --> costo: O(altezza + #{chiavi trovate})
			list(b->sx,n1,b->key-1); // OSS: ha senso ridurre l'intervallo così, ma non si risparmia molto
			cout << b->key << " ";
			list(b->dx,b->key+1,n2);
		}
	}
}

/* count */

// Obiettivo: O(h), dove h=altezza dell'albero

// il, ir sono booleani e tengono la memoria dell'(unica) esecuzione della else-clause finale
// (ovvero di quando si scende in un sottoalbero interamente contenuto nell'intervallo)
int count(bT b, int n1, int n2, int il, int ir)
{
	if(b == NULL) return 0;
	if(il && ir) return b->size; // se il sottoalbero in questione sta sia sopra n1 che sotto n2, è da contare per intero(!)
	if(b->key>n2){
		return count(b->sx,n1,n2,il,ir);
	} else if(b->key<n1){
		return count(b->dx,n1,n2,il,ir);
	} else {
		int lc=count(b->sx,n1,n2,il,1); // il sottoalbero sinistro sta tutto sotto n2
		int rc=count(b->dx,n1,n2,1,ir); // il sottoalbero sinistro sta tutto sopra n1
		return lc+rc+1;
	}
}

/* insert (keeps size field) */
// O(h), con h=altezza
void insertBST(bT *b, int v) // oppure si potrebbe fare una funzione di tipo `bT` che ritorna il nuovo albero, come sotto per delfromBST.
{
	if(*b == NULL){
		bT aux=new Node;
		aux->key=v;
		aux->sx=aux->dx=NULL;
		aux->size=1;
		*b=aux;
	} else if((*b)->key>v){
		(*b)->size+=1;
		insertBST(&((*b)->sx),v);
	} else if((*b)->key<v){ // l'albero per ipotesi non deve contenere duplicati, quindi non ne inseriamo ;)
		(*b)->size+=1;
		insertBST(&((*b)->dx),v);
	}
}

/* delete element from BST (in O(h), h=height) (keeps size field) */

// auxiliary function (finds maximum node of subtree, which is necessarily a leaf or a father with an only child)
bT maxsubtree(bT b) // OSS per ipotesi(ovvero per come viene chiamata questa funzione sotto), b!=NULL.
{
	while(b->dx != NULL){
		b->size-=1;
		b=b->dx;
	}
	return b;
}

bT delfromBST(bT b, int v)
{
	if(b != NULL){
		if(b->key==v){
			if(b->sx == NULL){
				bT t=b;
				b=b->dx;
				delete t;
			} else if(b->dx == NULL){
				bT t=b;
				b=b->sx;
				delete t;
			} else {
				bT c=maxsubtree(b->sx); // trova il massimo del sottoalbero a sinistra del nodo da cancellare(b), analogo sarebbe con il min del subtree destro
				b->key=c->key; // duplicazione
				b->size-=1; // il nodo da eliminare (che ora abbiamo sostituito con c) "perde" un nodo (il c originale, per l'appunto)
				b->sx=delfromBST(b->sx,c->key); // cancellazione del duplicato da b->sx, che è facile perché per costruzione c è proprio una foglia(oppure padre con figlio unico)
			}
		} else if(b->key>v){
			b->size-=1;
			b->sx=delfromBST(b->sx,v);
		} else if(b->key<v){
			b->size-=1;
			b->dx=delfromBST(b->dx,v);
		}
	}
	return b;
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
	bT B=buildBST(v,0,v.size()-1);

	// Visita simmetrica per verificare che il BST sia ordinato
	printBST(B);

	cout << "numero di operazioni: ";
	int k, n1, n2;
	char op;
	cin >> k;

	for(int i=0; i<k; i++){
		cout << "operazione " << i+1 << ": ";
		cin >> op >> n1;

		if(op == 'f'){
			printf("%d\n", (int)member(B,n1));
		} else if(op == 'l'){
			cin >> n2;
			cout << "list: ";
			list(B,n1,n2);
			cout << endl;
		} else if(op == 'r'){
			cin >> n2;
			cout << "range: " << count(B,n1,n2,0,0) << endl;
		} else if(op == 'i'){
			insertBST(&B,n1);
			printBST(B);
		} else if(op == 'd'){
			B=delfromBST(B,n1);
			printBST(B);
		}
	}

	// Visita posticipata per deallocare l'albero
	B=delBST(B);
	return 0;
}
