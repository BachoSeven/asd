 /*
  AREA DI PARCHEGGIO dei cursori
 *
*/

/*
  SEMPLICE DEBUG:
  1. mettere cout << "..." << Lendl << flush;
  2. partire dal main e, usando 1., individuare la funzione problematica
  3. andare in quella funzione e ripetere 2. nel corpo della funzione
*/

#include <iostream>
#include <vector>  // vector = lista di adiacenza
#include <list>    // coda per BFS implementata mediante lista

using namespace std;

#define ORIENTATO  // #define ORIENTATO vs #undef ORIENTATO
#ifdef ORIENTATO
constexpr auto OPENP  = "(";
constexpr auto CLOSEP = ")";
#else
constexpr auto OPENP  = "{";
constexpr auto CLOSEP = "}";
#endif

/* modo semplice per definire un grafo: liste di adiacenza */

constexpr auto MAXN = 1000; // massimo numero di nodi
vector<int>  adj[MAXN];     // array di MAXN vector = rappresentazione mediante liste di adiacenza
bool visitato[MAXN];        // array di booleani per stabilire quali nodi sono stati visitati
int N, M;                   // N <= NMAX numero di nodi, M = numero di archi

/*** lettura da input ***/

void leggiGrafo( ){
  freopen("input.txt", "r", stdin);  // redireziona la lettura da cin alla lettura del file specificato
  //freopen("output.txt", "w", stdout);

  cin >> N >> M;
  for (auto i = 0; i < M; i++){ // M archi
    int u, v;
    cin >> u >> v;              // arco uv non orientato
    // u--, v--; se partono da 1
    adj[u].push_back(v);        // v è nella lista di u
    adj[v].push_back(u);        // u è nella lista di v
  }
  // nota: grado(u) -> adj[u].size()
}

void leggiGrafoOrientato( ){
  // lettura grafo orientato da file "input_orientato.txt"
    //freopen("input_orientato.txt", "r", stdin);
    freopen("input_dag.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  cin >> N >> M;
  for (auto i = 0; i < M; i++){
    int u, v;
    cin >> u >> v;
    // u--, v--; se partono da 1
    adj[u].push_back(v);
  }
  // nota: grado_uscita(u) -> adj[u].size()

}

void stampaGrafo( ){
#ifdef ORIENTATO
  cout << "GRAFO orientato\n\n";
#else
  cout << "GRAFO (non orientato)\n\n";
#endif
  cout << "liste di adiacenza" << endl;
  for (auto u = 0; u < N; u++){
    cout << u << ": ";
    for ( auto v: adj[u] )
      cout << v << " ";
    cout << endl;
  }
  cout << endl;
}

/*** visita DFS in profondita' ***/

void DFSric( int u ){
  visitato[u] = true;
  for (auto v: adj[u])
    if (!visitato[v]) {
      cout << OPENP << u << ", " << v << CLOSEP << endl;
      DFSric(v);
    }
}

// esercizio per casa: classificare i vari archi come: tree, forward, back, cross
void DFS( ){
  for (auto u=0; u < N; u++)
    visitato[u] = false;
  cout << "DFS\n\nsequenza di archi che portano a nodi non ancora visitati: " << endl;
  for (auto u=0; u < N; u++)
    if (!visitato[u]) DFSric( u );
  cout << endl;
}


/*** visita DFS modificata per verificare aciclicità  ***/

bool incorso[MAXN];
bool aciclico;
int topologico[MAXN];
int ordine[MAXN];
int contatore;

void DFSric_mod( int u ){
  visitato[u] = incorso[u] = true;

  for (auto v: adj[u]){
    if (incorso[v])
      aciclico = false;  // arco uv back, quindi ciclo
    if (!visitato[v]) {
      cout << OPENP << u << ", " << v << CLOSEP << endl;
      DFSric_mod(v);
    }
  }
   incorso[u] = false;   // la visita di u è terminata
   topologico[u] = contatore--;
}

void DFS_mod( ){
  contatore = N-1;
  aciclico = true;
  for (auto u=0; u < N; u++)
    visitato[u] = incorso[u] = false;
  cout << "\nDFS\n\nsequenza di archi che portano a nodi non ancora visitati: " << endl;
  for (auto u=0; u < N; u++)
    if (!visitato[u]) DFSric_mod( u );
  cout << endl;
  cout << (aciclico ? "aciclico" : "ciclico") << endl << endl;
  if (aciclico){
    cout << "topological sort: " << endl;
    for (auto i=0; i < N; i++)
      cout << i << " ";
    cout << endl;
    for (auto u=0; u < N; u++)
      ordine[topologico[u]] = u;
    for (auto i=0; i < N; i++)
      cout << ordine[i] << " ";
    cout << endl << endl;
    for (auto i=0; i < N; i++)
      cout << i << " ";
    cout << endl;
    for (auto i=0; i < N; i++)
      cout << topologico[i] << " ";
    cout << endl << endl;
  }
}


/*** visita BFS in ampiezza (con distanze per grafi non pesati) ***/

void BFS( int s ){  // nodo s è un intero in [0..N-1]
  int distanza_da_s[MAXN];  // d(s,x) per ogni nodo x in grafo non pesato

  for (auto i=0; i<N; i++)
    visitato[i] = false;

  list<int> coda;       // implementata come std::list del C++: testa si chiama front e coda si chiama back
  coda.push_back(s);    // il nodo u di partenza è l'unico nella coda
  visitato[s] = true;   // (in)variante BFS: nella coda solo nodi visitati, la cui distanza da u è nota
  distanza_da_s[s] = 0; // d(s,s) = 0

  cout << "BFS\n\nsequenza di archi che portano a nodi non ancora visitati: " << endl;

  while( !coda.empty() ){
    /* estrazione della testa della coda */
    auto u = coda.front();  // FIFO: primo della coda (non viene estratto) e la sua distanza è definita
    coda.pop_front();  // FIFO: estrazione effettuata
    /* ogni vicino v di u va in coda solo se non è ancora visitato */
    for ( auto v: adj[u] )
      if (!visitato[v]){
        cout << OPENP << u << ", " << v << CLOSEP << endl;  // arco uv è di tipo: "tree edge" cioè è nell'abero BFS
        coda.push_back(v);
        visitato[v] = true;
        distanza_da_s[v] = distanza_da_s[u] + 1;
      }
  }

  cout << endl << "distanze da s = " << s << endl;
  for (auto u = 0; u < N; u++)
    cout << u << " : " << distanza_da_s[u] << endl;
  cout << endl;
}


/* MAIN */

int main(){
#ifdef ORIENTATO
  leggiGrafoOrientato();
#else
  leggiGrafo();
#endif
  stampaGrafo();
  //DFS();
  DFS_mod();
  //BFS(0);
  return 0;
}
