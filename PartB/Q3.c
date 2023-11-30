#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char** argv)
{
    int nRanks,rank,msg=64;
    char* buffer;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=2)
    {
        printf("Only 2 Processes allowed!");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("Process %d started\n",rank);
    while(msg<1000000000)
    {
        msg*=2;
        buffer=(char*)malloc(msg*sizeof(char));
        if(rank==0)
        {
            MPI_Send(buffer,msg,MPI_BYTE,1,1,MPI_COMM_WORLD);
            printf("Process 0 sent %d bytes to Process 1\n",msg);
            MPI_Recv(buffer,msg,MPI_BYTE,1,1,MPI_COMM_WORLD,&status);
        }
        else if(rank==1)
        {
            MPI_Recv(buffer,msg,MPI_BYTE,0,1,MPI_COMM_WORLD,&status);
            printf("Process 1 receive %d bytes from Process 0\n",msg);
            MPI_Send(buffer,msg,MPI_BYTE,0,1,MPI_COMM_WORLD);
        }
        free(buffer);
    }
    MPI_Finalize();
    return 0;
}