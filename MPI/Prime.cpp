#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "mpi.h"
using namespace std;

int main(int argc, char* argv[]) {

    int p,id;
    int first,last,sz;
    int multiple,next;
    int num;
    int n = 100000;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    
    if(id==0) cin>>num;
     if(n/p <= sqrt(n))
    {
        if(id == 1)
            printf("Pls enter a lesser number of processes \n");
        MPI_Finalize();
        exit (1);
    }


    if (num == 1 || num == 0 )
    {
       // if(id == 1)
       // {
            printf("The number %d is not prime",num);
         //   MPI_Finalize();
            exit(1);
       // }
    }
    

    first = floor(id*(n-2)/p);
    first += 2;
    last = floor((id+1)*(n-2)/p);
    last ++;
    sz = last - first;
    sz++;

    int arr[sz];

    for(int i = 0; i < sz; i++){
        arr[i] = 1; 
    }

    arr[0] = 0;
    arr[1] = 1;
    int k = 2;

    while(k*k <= n)
    {
        if(first % k != 0)
            multiple = k - first % k;
        else
            multiple = 0;

        for(int i = multiple; i < sz; i += k)
        {
            arr[i] = 0;
        }

        if(id == 0) 
            arr[k-2] = 1;

        if(id == 0)
        {
            next = k+1;
            while(arr[next - 2]==0) 
                next++;

            k = next;
        }

        MPI_Bcast (&k,  1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    for(int i = 0; i < sz; i++)
    {
       
        int actual_num;
        actual_num = floor(id*(n-2)/p) + 2;
        actual_num += i;

        //if(arr[i]) printf("%d\n",actual_num);
        if(arr[i] && actual_num==num)
            printf("1\n");
        if(!(arr[i]) && actual_num == num)
           printf("0\n");
    }

    MPI_Finalize();
}
