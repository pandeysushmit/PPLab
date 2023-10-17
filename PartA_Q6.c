#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
struct vec{
    int x;
    int y;
};
struct vec add(struct vec a,struct vec b){
    struct vec c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    return c;
}
int main(){
    int n=50000;
    struct vec arr[n],sum={0,0};
    for(int i=0;i<n;i++){
        arr[i].x=rand()%10;
        // printf("%d\t",arr[i].x);
        arr[i].y=rand()%10;
        // printf("%d\n",arr[i].y);
    }
    clock_t s,e;
    s=clock();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        #pragma omp critical
        {
            sum=add(sum,arr[i]);
        }
    }
    e=clock();
    printf("Sum: %d %d\n",sum.x,sum.y);
    printf("Time taken is: %lf\n",(double)(e-s)/CLOCKS_PER_SEC);
}