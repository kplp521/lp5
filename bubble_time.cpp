#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<ctime>
#include<cstdlib>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {
   	 int first = i % 2;

   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  )
   	   {
   		 if(  a[ j ]  >  a[ j+1 ]  )
   		  {
     			 swap(  a[ j ],  a[ j+1 ]  );
   		  }
   		   }
     }
}


void swap(int &a, int &b)
{

    int test;
    test=a;
    a=b;
    b=test;

}

int main()
{

    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    srand(time(0));
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>a[i];
    }

    bubble(a,n);

    cout<<"\n sorted array is=> ";
    for(int i=0;i<n;i++)
    {
   	 cout<<a[i]<<endl;
    }
    clock_t start = clock();
    bubble(a , n);
    clock_t end = clock();
    double sequentialBubbleTime = double(end-start) /CLOCKS_PER_SEC;
    start = clock();
    #pragma omp parallel
    {
        bubble(a,n);
    }
    end = clock();
    double parallelBubbleTime = double(end-start) /CLOCKS_PER_SEC;
    cout<<"sequential bubble sort time : "<<sequentialBubbleTime<<"sec"<<endl;
    cout<<"parallel bubble sort time : "<<parallelBubbleTime<<"sec"<<endl;
    delete[] a;

return 0;
}

