#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char role;
    int grade;
};

int main(int argc, char* argv[]) {
    printf("Number of arguments: %d\n", argc);
    int arr[2024] = {0};
    int init = 1;
    struct student me = {39924407, "student", 95};
    if (argc == 2) {
        init = atoi(argv[1]);
    }
    for (int i = 0; i < 2024; i++) {
        arr[i] = init;
    }
    return 0;
};