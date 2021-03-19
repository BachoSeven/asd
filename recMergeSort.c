#include <stdio.h>
#include <stdlib.h>

#define DIM 1000000

void unisci(int *a, int sx, int centro, int dx)
{
	int i=sx; // 0
	int j=centro+1; // 1
	int k=0;
	int b[dx-sx+1]; // lungo 2
	while ((i<=centro) && (j<=dx)) { // confronto i due pezzi
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

void mergesort(int *a, int sx, int dx)
{
	if(sx<dx) {
		int centro=(sx+dx)/2;
		mergesort(a,sx,centro);
		mergesort(a,centro+1,dx);
		unisci(a,sx,centro,dx);
	}
}

int main(void)
{
	int a[DIM];
	for(int i=0;i<DIM;i++) {
		/* scanf("%d",a+i); */
		*(a+i)=DIM-i; // ordinati al contrario
	}
	mergesort(a,0,DIM-1);
	for(int j=0;j<DIM;j++) {
		printf("%d ",*(a+j));
		printf("\n");
	}
	return 0;
}
