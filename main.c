#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void Demon_sort(int *arr, int begin, int end) {
    int len = end - begin;
    int tmp_arr[len];
    int left_max = INT_MIN, right_min = INT_MAX;
    int middle = begin + len / 2;
    int left_point, right_point;

    do {
        left_max = INT_MIN, right_min = INT_MAX;
        left_point = 0, right_point = len - 1;

        if (len == 1) {
            return;
        }
        for (int i = begin; i < middle; ++i) {
            if (arr[i] > left_max) left_max = arr[i];
        }
        for (int i = middle; i < end; ++i) {
            if (arr[i] < right_min) right_min = arr[i];
        }
        if (left_max <= right_min) {
            return;
        }
        if (len == 2) {
            if (arr[begin] > arr[end - 1]) {
                int buf = arr[begin];
                arr[begin] = arr[end - 1];
                arr[end - 1] = buf;
            }
            return;
        }
        for (int i = begin; i < middle; ++i) {
            if (arr[i] <= right_min) tmp_arr[left_point++] = arr[i];
            else tmp_arr[right_point--] = arr[i];
        }
        for (int i = middle; i < end; ++i) {
            if (arr[i] >= left_max) tmp_arr[right_point--] = arr[i];
            else tmp_arr[left_point++] = arr[i];
        }
        for (int i = begin, k = 0; i < end; ++i, ++k) {
            arr[i] = tmp_arr[k];
        }
        //free(tmp_arr);
        // tmp_arr = (int *) realloc(tmp_arr,sizeof (int));
        Demon_sort(arr, begin, middle);
        Demon_sort(arr, middle, end);

        left_max = INT_MIN, right_min = INT_MAX;
        for (int i = begin; i < middle; ++i) {
            if (arr[i] > left_max) left_max = arr[i];
        }
        for (int i = middle; i < end; ++i) {
            if (arr[i] < right_min) right_min = arr[i];
        }
        if (left_max <= right_min) {
            return;
        }
    } while (right_min < left_max);
}


int main() {
    srand(time(NULL));
    int len = 10000;
    int *arr;
    arr = (int *) malloc(len * sizeof(int));
    if (!arr)exit(-1);
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % 10000;
    }
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    Demon_sort(arr, 0, len);
    printf("\n");
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}
