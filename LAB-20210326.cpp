#include <iostream>
#include <cstdlib> // stdlib.h

using namespace std;

int *randArray(int l, int m)
{
	int i;

	int *A=new int[l];
	for(i=0;i<l;i++){
		A[i]=rand() % m;
	}
	return A;
}

void printArray(int *A, int l)
{
	int i;
	cout << "[";
	for(i=0;i<l-1;i++){
		cout << A[i] << ",";
	}
	cout << A[l-1] << "]\n";
}

void scambia(int *a, int *b) // dati due puntatori ad interi, scambia i loro valori
{
	*a+=*b;
	*b=*a-*b;
	*a-=*b;
}

int partizione(int *a, int sx, int px, int dx)
{
	int i=sx;
	int j=dx-1;

	if(px!=dx) { scambia(a+px,a+dx); }

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
		int px=rand() % (dx-sx+1) + sx; // scelgo il pivot in modo pseudorandom (si può fare anche `pivot= sx + rand() % (dx-sx);` )
		int rk=partizione(a,sx,px,dx);
		quickSort(a,sx,rk-1);
		quickSort(a,rk+1,dx);
	}
}

int rango(int *a, int s, int d, int r)
{
	int i;
	if(s==r){
		i=s;
	} else {
		int p=rand() % (d-s+1) + s;
		int mid=partizione(a,s,p,d);
		if(r==mid+1){
			i=mid;
		} else if(r<mid+1){
			i=rango(a,s,mid-1,r);
		} else {
			i=rango(a,mid+1,d,r);
		}
	}
	return i;
}

int main()
{
	int len;
	int max;
	int rk;
	int i;

	srand(time(NULL)); // seed per rand

	cout << "Inserire la lunghezza dell'array: ";
	cin >> len;

	cout << "Inserire un limite superiore per gli elementi dell'array: ";
	cin >> max;

	cout << "Inserire il rango dell'elemento da trovare: ";
	cin >> rk;

	int *a;
	a=randArray(len,max);

	cout << "Array ordiginale: ";
	printArray(a,len);

	int found=a[rango(a,0,len-1,rk)];
	cout << "L'elemento di rango " << rk << " è: " << found << endl;

	quickSort(a,0,len-1);

	cout << "Array ordinato: ";
	printArray(a,len);

	delete[] a;
	return 0;
}
