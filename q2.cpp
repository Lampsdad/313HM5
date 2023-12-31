// Compare the overhead of a system call with that of a function call.
// Write a program that measures the performance of a function call and a system call that does very little work in the kernel.
// FOR EXAMPLE: getpid
// Document your technique of measuring time for this problem.
// Tabulate the relative performace of the function call and the system call.
// Use a large number of invocations in each case and take the average
#include <iostream>
#include <ctime>
#include <unistd.h>


int customFunction() {
    int result = 0;
    result += 1;
    return result;
}

double MeasureFunctionCallTime(int numIterations) {
    clock_t start = clock();
    for (int i = 0; i < numIterations; i++) {
        customFunction();
    }
    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC / numIterations);
}

double MeasureSystemCallTime(int numIterations) {
    clock_t start = clock();
    for (int i = 0; i < numIterations; i++) {
        getpid();
    }
    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC / numIterations);
}

int main() {
    int numIterations = 20000;
    double functionCallTime = MeasureFunctionCallTime(numIterations);
    double systemCallTime = MeasureSystemCallTime(numIterations);
    std::cout << "Function call time: " << (functionCallTime * 1000000) << "Micro Seconds" << std::endl;
    std::cout << "System call time: " << (systemCallTime * 1000000)  << "Micro Seconds" << std::endl;
    return 0;
}