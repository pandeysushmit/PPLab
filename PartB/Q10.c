#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
#define n 20
int main(int argc, char** argv)
{
    int nRanks,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=4)
    {
        printf("Only 4 Process are allowed!");
        MPI_Finalize();
        return 0;
    }
    int arr[n],localArr[n/nRanks],localSum=0,sum[nRanks];
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
        for(int i=0;i<n;i++)
            arr[i]=i+1;
    }
    MPI_Scatter(arr,n/nRanks,MPI_INT,localArr,n/nRanks,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<n/nRanks;i++)
        localSum+=localArr[i];
    MPI_Gather(&localSum,1,MPI_INT,sum,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("Original Array: ");
        for(int i=0;i<n;i++)
            printf("%d ",arr[i]);
        printf("\n");
        printf("Sum for all processes are:\n");
        for(int i=0;i<nRanks;i++)
            printf("Process: %d Sum: %d\n",i,sum[i]);
    }
    MPI_Finalize();
    return 0;
}