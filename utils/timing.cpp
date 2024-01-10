// Description: Timing utilities
#include <functional>
#include <ctime>

using namespace std;

double time_measure(const function<void()>& f) {
    clock_t start = clock();
    f();
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}