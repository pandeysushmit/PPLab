#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argv,char** argc)
{
    int nRanks,rank,size=64;
    double start,end,time,bandwidth;
    char* buffer;
    MPI_Status status;
    MPI_Init(&argv,&argc);
    MPI_Comm_size(MPI_COMM_WORLD,&nRanks);
    if(nRanks!=2)
    {
        printf("Only 2 Process are allowed!");
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    while(size<1000000)
    {
        buffer=(char*)malloc(size*sizeof(char));
        start=MPI_Wtime();
        if(rank==0)
        {
            MPI_Sendrecv(buffer,size,MPI_BYTE,1,1,buffer,size,MPI_BYTE,1,1,MPI_COMM_WORLD,&status);
        }
        else if(rank==1)
        {
            MPI_Sendrecv(buffer,size,MPI_BYTE,0,1,buffer,size,MPI_BYTE,0,1,MPI_COMM_WORLD,&status);
        }
        end=MPI_Wtime();
        time=end-start;
        printf("Message Size: %d bytes Time Taken:%f s Bandwidth:%lf\n",size,time,(double)((size/time)/(1024*1024)));
        free(buffer);
        size*=2;
    }
    MPI_Finalize();
    return 0;
}