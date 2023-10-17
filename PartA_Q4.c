#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
int fibo(int n){
    if(n<=1)
        return n;
    int a,b;
    #pragma omp task shared(a) firstprivate(n)
    a=fibo(n-1);
    #pragma omp task shared(b) firstprivate(n)
    b=fibo(n-2);
    #pragma omp taskwait
    return a+b;
}
int main(){
    clock_t s,e;
    int n;
    scanf("%d",&n);
    s=clock();
    for(int i=0;i<n;i++){
        printf("Term %d is %d\n",i+1,fibo(i));
    }
    e=clock();
    printf("Time Taken is: %lf\n",(double)(e-s)/CLOCKS_PER_SEC);
}