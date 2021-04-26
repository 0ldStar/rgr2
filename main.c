#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Demon(int *arr, int len) {

}


int main() {
    srand(time(NULL));
    int *arr = (int *) malloc(10 * sizeof(int));
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand() % 100;
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d ",arr[i]);
    }
    return 0;
}
