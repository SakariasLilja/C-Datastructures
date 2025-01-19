/**
 * @brief Measures the performance of the list's append method
 * 
 * @return float* An array of times for appends of size: [100, 1000, 10000, 100000]
 */
float* listAddPerformance();

/**
 * @brief Consumes a list performance test and prints out the times
 * 
 * @param func Performance function to test
 * @return int If the test was successfully run
 */
int listPerformanceTest(float*(*func)());