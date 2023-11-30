#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    int nRanks,rank,root=0,value;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=4)
    {
        printf("Only 4 Processes allowed!");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    value=(rank+1)*100;
    printf("Process %d have value:%d\n",rank+1,value);
    if(rank==root)
    {
        int buffer[4];
        MPI_Gather(&value,1,MPI_INT,buffer,1,MPI_INT,root,MPI_COMM_WORLD);
        printf("Values collected by process %d are: %d %d %d %d",rank+1,buffer[0],buffer[1],buffer[2],buffer[3]);
    }
    else
    {
        MPI_Gather(&value,1,MPI_INT,NULL,0,MPI_INT,root,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}