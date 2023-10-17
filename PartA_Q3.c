#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
int main(){
    int n,m;
    scanf("%d %d",&m,&n);
    int arr[m][n];
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            arr[i][j]=0;
    #pragma omp parallel for num_threads(m) schedule(static,2)
    for(int i=0;i<n;i++){
        int id=omp_get_thread_num();
        arr[id][i]=1;
    }
    for(int i=0;i<m;i++){
        printf("Thread %d executed",i+1);
        for(int j=0;j<n;j++){
            if(arr[i][j])
                printf(" iteration %d",j);
        }
        printf("\n");
    }
    return 0;
}