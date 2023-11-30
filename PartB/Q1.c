#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
    int nRanks,rank,buffer;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=2)
    {
        printf("Needs exactly two ranks.\n");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
        buffer=100;
        printf("Sending %d to process %d\n",buffer,1);
        MPI_Send(&buffer,1,MPI_INT,1,1,MPI_COMM_WORLD);
    }
    if(rank==1)
    {
        MPI_Recv(&buffer,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        printf("Received %d from %d\n",buffer,0);
    }
    MPI_Finalize();
    return 0;
}