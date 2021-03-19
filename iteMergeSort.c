#include <stdio.h>
#include <stdlib.h>

#define DIM 1000000

int min(int x, int y) { return (x<y)? x :y; }

void unisci(int *a, int sx, int centro, int dx)
{
	int i=sx;
	int j=centro+1;
	int k=0;
	int b[dx-sx+1];
	/* confronto i due pezzi */
	while ((i<=centro) && (j<=dx)) {
		if (*(a+i)<=*(a+j)) {
			*(b+k)=*(a+i);
			i++;
		} else {
			*(b+k)=*(a+j);
			j++;
		}
		k++;
	}
	/* copio gli elementi rimanenti */
	for (;i<=centro;i++,k++) {
		*(b+k)=*(a+i);
	}
	for (;j<=dx;j++,k++) {
		*(b+k)=*(a+j);
	}
	/* ricopio i due sottoarray nell'array principale */
	for (int t = sx; t <= dx; t++) {
		*(a+t)=*(b+t-sx);
	}
}

void mergesortiterativo(int *a)
{
	for (int size=1; size<DIM; size = 2*size) {
		for (int start=0; start<DIM-1; start += 2*size) { // 2*size perchè voglio creare subarray lunghi il doppio ogni volta
			int mid = min(start + size - 1, DIM-1);
			int end = min(start + 2*size - 1, DIM-1);
			unisci(a, start, mid, end);
		}
	}
}

int main(void)
{
	int a[DIM];
	for(int i=0;i<DIM;i++) {
		/* scanf("%d",a+i); */
		*(a+i)=DIM-i; // ordinati al contrario
	}
	mergesortiterativo(a);
	/* for(int j=0;j<DIM;j++) { */
		/* printf("%d ",*(a+j)); */
		/* printf("\n"); */
	/* } */
	return 0;
}
