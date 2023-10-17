#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
int n = 100000;
void combine(int arr[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = 0;
    int temp[n];
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            temp[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = arr[j];
            k++;
            i++;
        }
    }
    while (i <= mid)
    {
        temp[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        temp[k] = arr[j];
        k++;
        j++;
    }
    for(int i=low;i<=high;i++)
        arr[i]=temp[i];
}
void seq_merge(int arr[],int low,int high){
    if(low>=high) return;
    int mid=(low+high)/2;
    seq_merge(arr,low,mid);
    seq_merge(arr,mid+1,high);
    combine(arr,low,mid,high);
}
void par_merge(int arr[],int low,int high){
    if(low>=high) return;
    int mid=(low+high)/2;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            par_merge(arr,low,mid);
        }
        #pragma omp section
        {
            par_merge(arr,mid+1,high);
        }
    }
    combine(arr,low,mid,high);
}
int main()
{
    int arr[n];
    // srand(time(0));
    clock_t start1, end1, start2, end2;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
    int arr1[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr[i];
    }
    start1=clock();
    seq_merge(arr, 0, n - 1);
    end1=clock();
    printf("Sequential merge sort took %lf seconds\n",(double) (end1-start1)/CLOCKS_PER_SEC);
    start2 = clock();
    par_merge(arr1, 0, n - 1);
    end2 = clock();
    printf("Parallel merge sort took %lf seconds\n",(double) (end2-start2)/CLOCKS_PER_SEC);
    return 0;
}