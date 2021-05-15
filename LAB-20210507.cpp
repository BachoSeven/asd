#include <iostream>
#include <vector>		 // vector per le liste di adiacenza
#include <list>			 // lista per implementare la coda per BFS (vedi reference cpp per funzioni per operare su liste)

using namespace std;

#define ORIENTATO  // oppure #undef ORIENTATO

/* modo semplice per definire un grafo: liste di adiacenza */

constexpr auto MAXN = 1000; // massimo numero di nodi
vector<int> adj[MAXN];     // array di MAXN vector = rappresentazione mediante liste di adiacenza
bool visitato[MAXN];				// array di booleani per stabilire quali nodi sono stati visitati
int N,M;										// N <= MAXN numero di nodi, M = numero di archi

/* lettura da input */

void leggiGrafoOrientato()
{
	freopen("input.txt", "r", stdin); // redireziona la lettura da stdin alla lettura di un file

	cin >> N >> M;

	for(auto i=0;i<M;i++){ // M archi
		int u,v;
		cin >> u >> v; 			// arco uv non orientato
		adj[u].push_back(v);// v è nella lista di u
		adj[v].push_back(u);// u è nella lista di v
	}
	// nota: grado(u) --> adj[u].size()
}

void leggiGrafo()
{
	freopen("input_orientato.txt", "r", stdin); // redireziona la lettura da stdin alla lettura di un file

	cin >> N >> M;

	for(auto i=0;i<M;i++){ // M archi
		int u,v;
		cin >> u >> v; 			// arco uv non orientato
		adj[u].push_back(v);// v è nella lista di u
	}
	// nota: grado(u) --> adj[u].size()
}

void stampaGrafo()
{
	cout << "liste di adiacenza" << endl;
	for(auto u=0;u<N;u++){
		cout << u << ": ";
		for(auto v:adj[u]) // NOICE
			cout << v << " ";
		cout << endl;
	}
}

/* Visita BFS in ampiezza */
void BFS(int s) // s è il nodo di partenza, intero in [0...N-1]
{
	for(auto i=0;i<N;i++)
		visitato[i]=false;

	int distanza_da_s[MAXN]; // OPZIONALE: mi da d(s,x) per ogni x in grafo non pesato

	list<int> coda; 		// begin è front, end è back
	coda.push_back(s);	// il nodo s di partenza è l'unico in coda (abbiamo fatto una enqueue)
	visitato[s]=true;		// (in)variante BFS: nella coda ci sono solo nodi visitati, di cui conosciamo la distanza da s

	distanza_da_s[s]=0; // OPZIONALE: d(s,s)=0

	cout << "sequenza di archi che portano a nodi non ancora visitati: " << endl;

	while(!coda.empty()){
		auto u=coda.front();	// FIFO: il primo della coda(non viene estratto) (e conosciamo la sua distanza da s)
		coda.pop_front(); // FIFO: estrazione del primo della coda
		/* ogni vicino v di u va in coda solo se non è ancora visitato */
		for(auto v:adj[u]){
			if(!visitato[v]){
				cout << "{"<< u << ", " << v << "}" << endl; // uv è di tipo `tree-edge`, cioè sta nell'albero BFS
				// enqueue
				coda.push_back(v);
				visitato[v]=true;
				distanza_da_s[v]=distanza_da_s[u]+1; // OPZIONALE: quando visito un nodo, so la sua distanza
			}
		}
	}
	// OPZIONALE
	cout << endl << "distanze da s:" << endl;
	for(auto u=0;u<N;u++)
		cout << u << ": " << distanza_da_s[u] << endl;
}

/* Visita DFS in profondità */
void DFSrec(int u)
{
	visitato[u]=true;
	for(auto v:adj[u])
		if(!visitato[v]){
			cout << "{"<< u << ", " << v << "}" << endl;
			DFSrec(v);
		}
}

// TODO(Esercizio per casa): classificare i vari archi(in tree,forward,back oppure cross)
void DFS()
{
	int cc=0;
	for(auto i=0;i<N;i++) // inizializzazione: nessun nodo visitato
		visitato[i]=false;

	for(auto i=0;i<N;i++)
		if(!visitato[i]){
			cc++;
			cout << "- " << cc << "a componente connessa: "  <<  i  << endl;
			DFSrec(i);
		}
}

int main()
{
#ifdef ORIENTATO
	leggiGrafo();
#else
	leggiGrafoOrientato();
#endif

	stampaGrafo();
	cout << endl;

	BFS(0);
	cout << endl;

	DFS();
	return 0;
}
