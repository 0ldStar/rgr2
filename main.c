#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void Demon_sort(int *arr, int begin, int end) {
    int len = end - begin;
    int *tmp_arr = (int *) malloc(len * sizeof(int));
    int left_max = INT_MIN, right_min = INT_MAX;
    int middle = len / 2;
    int left_point = begin, right_point = end;
    printf("middle = %d len %d [%d %d]\n", middle, len, begin, end);
    for (int i = begin; i < end; ++i) {
        printf("%d ", arr[i]);
    }
    if (len == 1){
        printf("ONE\n");
        return;}
   /* if ((len == 2) && (arr[begin] > arr[end])) {
        int buf = arr[begin];
        arr[begin] = arr[end];
        arr[end] = buf;
        printf("TWO\n");
        return;
    }*/
    printf("\n");
    for (int i = begin; i < middle; ++i) {
        if (arr[i] < right_min) right_min = arr[i];
    }
    for (int i = middle; i < end; ++i) {
        if (arr[i] > left_max) left_max = arr[i];
    }
    if (left_max < right_min) {
        return;
    }

    for (int i = begin; i < middle; ++i) {
        if (arr[i] < right_min) tmp_arr[left_point++] = arr[i];
        else tmp_arr[right_point--] = arr[i];
    }
    for (int i = middle; i < end; ++i) {
        if (arr[i] < right_min) tmp_arr[left_point++] = arr[i];
        else tmp_arr[right_point--] = arr[i];
    }
    for (int i = begin; i < end; ++i) {
        arr[i]= tmp_arr[i];
    }
    Demon_sort(arr, begin, middle);
    Demon_sort(arr, middle, end);
}


int main() {
    srand(time(NULL));
    int *arr = (int *) malloc(10 * sizeof(int));
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand() % 100;
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    Demon_sort(arr, 0, 10);
    printf("\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}
