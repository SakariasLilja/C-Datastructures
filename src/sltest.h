const int TEST_SIZE = 10;
const unsigned int ARR[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

/**
 * @brief Measures the performance of the list's append method
 * 
 * @return float* An array of times in ms with size 10
 */
float* listAddPerformance();

/**
 * @brief Consumes a list performance test and prints out the times
 * 
 * @param func Performance function to test
 * @return int If the test was successfully run
 */
int listPerformanceTest(float*(*func)());

/**
 * @brief Measures the performance of the list's sort method
 * 
 * @return float* An array of times in ms with size 10
 */
float* listSortPerformance();