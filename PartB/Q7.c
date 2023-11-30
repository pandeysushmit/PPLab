#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int rank,buffer,root=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==root)
    {
        buffer=100;
        printf("Broadcasting buffer value from %d to all Processes\n",root);
    }
    MPI_Bcast(&buffer,1,MPI_INT,root,MPI_COMM_WORLD);
    if(rank!=root)
    {
        printf("Process %d with buffer value: %d\n",rank,buffer);
    }
    MPI_Finalize();
    return 0;
}