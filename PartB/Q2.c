#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv)
{
    char* buffer;
    int nRanks,rank,msg=32;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=2)
    {
        printf("Number of processes must be 2\n");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("Process %d started\n",rank);
    fflush(stdout);
    while(msg<100000)
    {
        msg*=10;
        buffer= (char*)malloc(msg*sizeof(char));
        if(rank==0)
        {
            MPI_Send(buffer,msg,MPI_BYTE,1,1,MPI_COMM_WORLD);
            printf("Process 0 sent %d byte to process 1\n",msg);
            fflush(stdout);
            MPI_Recv(buffer,msg,MPI_BYTE,1,1,MPI_COMM_WORLD,&status);
        }
        if(rank==1)
        {
            MPI_Send(buffer,msg,MPI_BYTE,0,1,MPI_COMM_WORLD);
            printf("Process 1 send %d to process 0\n",msg);
            fflush(stdout);
            MPI_Recv(buffer,msg,MPI_BYTE,0,1,MPI_COMM_WORLD,&status);
        }
        free(buffer);
    }
    MPI_Finalize();
    return 0;
}