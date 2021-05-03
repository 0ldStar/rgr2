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
void call(int len) {
    int *arr;
    long time_start, time_finish;
    arr = (int *) malloc(len * sizeof(int));
    if (!arr)exit(-1);
    FILE *fp;
    if ((fp = fopen("write.txt", "a")) == NULL) {
        printf("Can't open file 'write.txt'\n");
        exit(-1);
    }/*
    char c;
    do {
        c = fgetc(fp);
    } while (c != '\n');
*/
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % 10000;
    }
    time_start = clock();
    Demon_sort(arr, 0, len);
    time_finish = clock();
    fprintf(fp,"%d %li\n",len, time_finish -time_start);
    fclose(fp);
    free(arr);
}

int main() {
    srand(time(NULL));
    call(10);
    call(100);
    call(1000);
    call(10000);
    return 0;
}
