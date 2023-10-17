#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
int main(){
    int n;
    scanf("%d",&n);
    int sum=0;
    #pragma omp parallel for
    for(int i=1;i<=n;i++){
        #pragma omp critical
        sum+=i;
    }
    printf("Sum: %d\n",sum);
}