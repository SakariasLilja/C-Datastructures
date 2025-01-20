extern const int TEST_SIZE;
extern const unsigned int ARR[];

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

/**
 * @brief Measures the performance of the list's reverse method
 * 
 * @return float* An array of times in ms with size 10
 */
float* listReversePerformance();