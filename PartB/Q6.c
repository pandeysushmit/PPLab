#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int nRanks,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
        printf("Entering Phase 1\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("Entering phase 2\n");
    }
    printf("Process %d in Phase 2\n",rank);
    MPI_Finalize();
    return 0;
}