#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void Demon_sort(int *arr, int begin, int end) {
    int len = end - begin;
    int *tmp_arr = (int *) malloc(len * sizeof(int));
    int left_max = INT_MIN, right_min = INT_MAX;
    int middle = begin + len / 2;
    int left_point, right_point;
    //printf("middle = %d len %d [%d %d]\n", middle, len, begin, end);

    do {
        left_max = INT_MIN, right_min = INT_MAX;
        left_point = 0, right_point = len - 1;

        /*for (int i = begin; i < end; ++i) {
            printf("%d ", arr[i]);
        }*/
        if (len == 1) {
           // printf("ONE\n");
            return;
        }
        //printf("\n");
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
            /*for (int i = 0; i < begin; ++i) {
                printf("   ");
            }
            for (int i = begin; i < end; ++i) {
                printf("%d ",arr[i]);
            }
            printf("\n");*/
           // printf("TWO\n %d %d\n", arr[begin], arr[end - 1]);
            return;
        }
       // printf("max = %d min = %d\n", left_max, right_min);
        for (int i = begin; i < middle; ++i) {
            if (arr[i] <= right_min) tmp_arr[left_point++] = arr[i];
            else tmp_arr[right_point--] = arr[i];
        }
        for (int i = middle; i < end; ++i) {
            if (arr[i] >= left_max) tmp_arr[right_point--] = arr[i];
            else tmp_arr[left_point++] = arr[i];
        }

        //printf("TMP\n");
        for (int i = begin, k = 0; i < end; ++i, ++k) {
            arr[i] = tmp_arr[k];
            //printf("%d ", arr[i]);
        }
        /*for (int i = 0; i < begin; ++i) {
            printf("   ");
        }
        for (int i = begin; i < end; ++i) {
            printf("%d ",arr[i]);
        }
        printf("\n");*/
       // printf("\n\n");
        Demon_sort(arr, begin, middle);
        Demon_sort(arr, middle, end);
       // printf("B%d D%d L%d R%d\n", begin, end, left_max, right_min);
        /*for (int i = begin; i < end; ++i) {
            printf("%d ",arr[i]);
        }*/
       // printf("\n");
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
        //printf("\tL%d R%d\n", left_max, right_min);
    } while (right_min < left_max);
}


int main() {
    srand(time(NULL));
    int len = 1000;
    int *arr = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % 100;
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
    return 0;
}
