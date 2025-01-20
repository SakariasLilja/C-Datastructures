#include "sltest.h"

const int TEST_SIZE = 10;
const unsigned int ARR[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

int main() {
    listPerformanceTest(listReversePerformance);
    
    return 0;
}