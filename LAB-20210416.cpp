// input: array A
// output: numero di inversioni presenti in A, ovvero:
//				 le coppie del tipo (i,j), con i<j,
// 				 tali che A[i]>A[j].
// ipotesi: A non contiene duplicati

#include <iostream>

#define DIM 10

int invCount(int *a, int sx, int dx)
{
	int r=0;
	if(sx!=dx) {
		int centro=(sx+dx)/2;			  // divide

		r+=invCount(a,sx,centro);   // impera
		r+=invCount(a,centro+1,dx);

		if(a[centro]>a[centro+1]) { // ricombina
			r+=1;
		}
	}
	return r;
}

int main(void)
{
	int a[DIM];
	for(int i=0;i<DIM;i++) {
		scanf("%d",a+i);
		// *(a+i)=DIM-i; // ordinati al contrario
	}
	int count=invCount(a,0,DIM-1);
	printf("%d\n",count);
	return 0;
}
