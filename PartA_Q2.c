#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
int n=900000;
void pi_seq(){
    double sum=0;
    for(int i=0;i<n;i++){
        double a=(i%2==0?1.0:-1.0)/(2*i+1);
        sum+=a;
    }
    double pi=4.0*sum;
    printf("Serial Pi=%f\n",pi);
}
void pi_par(){
    double sum=0;
    #pragma omp parallel for
    for(int i=0;i<n;i++)
    {
        double a=(i%2==0?1.0:-1.0)/(2*i+1);
        #pragma omp critical
        {
            sum+=a;
        }
    }
    double pi=4.0*sum;
    printf("Parallel Pi=%f\n",pi);
}
int main(){
    clock_t s1,e1,s2,e2;
    s1=clock();
    pi_seq();
    e1=clock();
    printf("Time for serial: %f\n",(double)(e1-s1)/CLOCKS_PER_SEC);
    s2=clock();
    pi_par();
    e2=clock();
    printf("Time for parallel: %f\n",(double)(e2-s2)/CLOCKS_PER_SEC);
    return 0;
}