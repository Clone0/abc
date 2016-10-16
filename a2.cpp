#include<iostream>
#include<stdlib.h>
#include<pthread.h>
using namespace std;
struct arr{
	int *a;
	int start;
	int end;
};
int n;
void *quick(void * in){
	arr *a=(arr*)in;
	int temp;
	if(a->start < a->end){
		int i,j;
		int pivot;
		i=a->start;
		j=a->end;
		pivot=a->a[a->start];
		while(i<j){
			while(a->a[i] <= pivot && i<j){
				i++;
			}
			while(a->a[j] > pivot && i<=j)
			{
				j--;
			}
			if(i<j){
				temp=a->a[i];
				a->a[i]=a->a[j];
				a->a[j]=temp;
			}
		}
		temp=a->a[j];
		a->a[j]=a->a[a->start];
		a->a[a->start]=temp;
		pthread_t id=pthread_self();
		cout<<"Thread ID "<<id<<" for pivot "<<pivot<<"\n";
		arr a1,a2;
		a1.a=new int[n];
		a2.a=new int[n];
		a1.a=a->a;
		a2.a=a->a;
		a1.start=a->start;
		a1.end=j-1;
		a2.start=j+1;
		a2.end=a->end;
		pthread_t thread[2];
		pthread_create(&thread[0],NULL,&quick,(void *)&a1);
		pthread_create(&thread[1],NULL,&quick,(void *)&a2);
		pthread_join(thread[0],NULL);
		pthread_join(thread[1],NULL);
	}	
}
int main()
{
	arr a;
	cout<<"Enter the number of elements\n";	
	cin>>n;
	a.a=new int[n];
	a.start=0;
	a.end=n-1;
	cout<<"Enter the elements of the array\n";
	for(int i=0 ; i< n; i++){
		cin>>a.a[i];
	}
	quick(&a);
	cout<<"The sorted elements are\n";
	for(int i=0 ; i< n; i++){
		cout<<a.a[i]<<"\t";
	}
	cout<<"\n";
}
