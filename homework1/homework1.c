#include <stdio.h>
#include <math.h>

char choose_mover(int load) {
    int aliceMax = 24;
    int bobMax = 31;
    int aliceCharge = 200;
    int bobCharge = 260;
    if ((load/aliceMax+1)*aliceCharge < (load/bobMax+1)*bobCharge) {
        return 'A';
    }
    else {
        return 'B';
    }
}

int find_divisor(int length, int arr[]) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (arr[i]%arr[j] == 0 && i != j) {
                int sum = arr[i]+arr[j];
                return sum;
            }
            else if (arr[j]%arr[i] == 0 && i != j) {
                int sum = arr[i]+arr[j];
                return sum;
            }
        }
    }
    return 0;
}

int powers(int num) {
    int powers = 0;
    for (int i = 2; i < num; i++) {
        for (int j = 2; pow(i,j) <= num; j++) {
            if (pow(i,j) <= num) {
                powers++;
            }
        }
    }
    return powers;
}

int fibonacci(int n) {
    int fib_1 = 1;
    int fib_2 = 1;
    for (int i = 1; i < n; i++) {
        int fib_3 = fib_2 + fib_1;
        fib_1 = fib_2;
        fib_2 = fib_3;
    }
    return fib_2;
}

int main() {
    return 0;
};