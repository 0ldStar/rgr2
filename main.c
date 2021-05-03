#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int Demon_sort_calc(int *arr, int begin, int end, int *left_max, int *right_min) {
    int len = end - begin;
    int middle = begin + len / 2;
    int *tmp_arr;
    while (!(tmp_arr = (int *) malloc(len * sizeof(int)))) {
        printf("MEM FAULT\n");
        exit(-1);
    }
    *left_max = INT_MIN, *right_min = INT_MAX;
    int left_point = 0, right_point = len - 1;

    if (len == 1) {
        free(tmp_arr);
        return -1;
    }
    for (int i = begin; i < middle; ++i) {
        if (arr[i] > *left_max) *left_max = arr[i];
    }
    for (int i = middle; i < end; ++i) {
        if (arr[i] < *right_min) *right_min = arr[i];
    }
    if (*left_max <= *right_min) {
        free(tmp_arr);
        return -1;
    }
    if (len == 2) {
        if (arr[begin] > arr[end - 1]) {
            int buf = arr[begin];
            arr[begin] = arr[end - 1];
            arr[end - 1] = buf;
        }
        free(tmp_arr);
        return -1;
    }
    for (int i = begin; i < middle; ++i) {
        if (arr[i] <= *right_min) tmp_arr[left_point++] = arr[i];
        else tmp_arr[right_point--] = arr[i];
    }
    for (int i = middle; i < end; ++i) {
        if (arr[i] >= *left_max) tmp_arr[right_point--] = arr[i];
        else tmp_arr[left_point++] = arr[i];
    }
    for (int i = begin, k = 0; i < end; ++i, ++k) {
        arr[i] = tmp_arr[k];
    }
    free(tmp_arr);
    return 0;
}

void Demon_sort(int *arr, int begin, int end) {
    int len = end - begin;
    int left_max = INT_MIN, right_min = INT_MAX;
    int middle = begin + len / 2;

    do {
        if (Demon_sort_calc(arr, begin, end, &left_max, &right_min) == -1)return;

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
    int len = 1000;
    int *arr;
    arr = (int *) malloc(len * sizeof(int));
    if (!arr)exit(-1);
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % 10000;
    }
    Demon_sort(arr, 0, len);

    printf("\nTIME: %li\n", clock());
    free(arr);
    return 0;
}
