#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int nRanks,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=4)
    {
        printf("Only 4 Processes are allowed!");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int value=rank+10;
    int max=0,min=0,sum=0,prod=0;
    MPI_Allreduce(&value,&max,1,MPI_INT,MPI_MAX,MPI_COMM_WORLD);
    printf("Process %d: The Maximum of all: %d\n",rank,max);
    MPI_Allreduce(&value,&min,1,MPI_INT,MPI_MIN,MPI_COMM_WORLD);
    printf("Process %d: The Minimum of all: %d\n",rank,min);
    MPI_Allreduce(&value,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    printf("Process %d: The Maximum of all: %d\n",rank,sum);
    MPI_Allreduce(&value,&prod,1,MPI_INT,MPI_PROD,MPI_COMM_WORLD);
    printf("Process %d: The Maximum of all: %d\n",rank,prod);
    MPI_Finalize();
    return 0;
}