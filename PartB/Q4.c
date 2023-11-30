#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int nRanks,rank,buffer=100;
    MPI_Status status;
    MPI_Request request;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks<2)
    {
        printf("Number of process should be 2 or more!\n");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
        MPI_Isend(&buffer,1,MPI_INT,1,1,MPI_COMM_WORLD,&request);
        MPI_Irecv(&buffer,1,MPI_INT,1,1,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);
        printf("Process 0 received %d from Process 1\n",buffer);
    }
    else if(rank==1)
    {
        MPI_Irecv(&buffer,1,MPI_INT,0,1,MPI_COMM_WORLD,&request);
        MPI_Isend(&buffer,1,MPI_INT,0,1,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);
        printf("Process 1 sent %d to Process 0\n",buffer);
    }
    MPI_Finalize();
    return 0;
}