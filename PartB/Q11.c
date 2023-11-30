#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int nRanks,rank,root=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=4)
    {
        printf("Only 4 Process are allowed!");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int arr[10];
    for(int i=0;i<10;i++)
        arr[i]=(rank+1)*(i+1);
    int max[10],min[10],sum[10],prod[10];
    MPI_Reduce(arr,max,10,MPI_INT,MPI_MAX,root,MPI_COMM_WORLD);
    MPI_Reduce(arr,min,10,MPI_INT,MPI_MIN,root,MPI_COMM_WORLD);
    MPI_Reduce(arr,sum,10,MPI_INT,MPI_SUM,root,MPI_COMM_WORLD);
    MPI_Reduce(arr,prod,10,MPI_INT,MPI_PROD,root,MPI_COMM_WORLD);
    if(rank==root)
    {
        printf("Reduction Results:\n");
        printf("Max Array: ");
        for(int i=0;i<10;i++)
            printf("%d ",max[i]);
        printf("\n");
        printf("Min Array: ");
        for(int i=0;i<10;i++)
            printf("%d ",min[i]);
        printf("\n");
        printf("Sum Array: ");
        for(int i=0;i<10;i++)
            printf("%d ",sum[i]);
        printf("\n");
        printf("Product Array: ");
        for(int i=0;i<10;i++)
            printf("%d ",prod[i]);
    }
    MPI_Finalize();
    return 0;
}