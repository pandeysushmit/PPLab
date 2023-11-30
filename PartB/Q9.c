#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int nRanks,rank,value,root=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=4)
    {
        printf("Only 4 Process are allowed!\n");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==root)
    {
        int buffer[4]={100,200,300,400};
        printf("The buffer values are: %d %d %d %d from Process %d\n",buffer[0],buffer[1],buffer[2],buffer[3],rank);
        MPI_Scatter(buffer,1,MPI_INT,&value,1,MPI_INT,root,MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(NULL,0,MPI_INT,&value,1,MPI_INT,root,MPI_COMM_WORLD);
    }
    printf("Process %d received %d\n",rank,value);
    MPI_Finalize();
    return 0;
}