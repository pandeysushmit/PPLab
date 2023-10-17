#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
int isPrime(int n){
    if(n<=1)
        return 0;
    #pragma omp parallel for
    for(int i=2;i<n;i++){
        if(n%i==0)
            return 0;
    }
    return 1;
}
int main(){
    int n;
    scanf("%d",&n);
    clock_t s1,e1,s2,e2;
    s1=clock();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        if(isPrime(i))
            continue;
            // printf("%d\t",i);
    }
    printf("\n");
    e1=clock();
    printf("Time for Parallel Execution: %lf\n",(double)(e1-s1)/CLOCKS_PER_SEC);
    s2=clock();
    for(int i=0;i<n;i++){
        if(isPrime(i))
            continue;
            // printf("%d\t",i);
    }
    e2=clock();
    printf("\n");
    printf("Time for Serial Execution: %lf\n",(double)(e2-s2)/CLOCKS_PER_SEC);
}