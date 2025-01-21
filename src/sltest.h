#ifndef TEST_H
#define TEST_H

extern const int TEST_SIZE;
extern const unsigned int ARR[];

/**
 * @brief Prepares the system to measure data correctly
 */
void warmup();

/**
 * @brief Consumes a list performance test and prints out the times
 * 
 * @param func Performance function to test
 * @return int If the test was successfully run
 */
int performanceTest(float*(*func)());

/**
 * @brief Measures the performance of the list's append method
 * 
 * @return float* An array of times in ms
 */
float* listAddPerformance();

/**
 * @brief Measures the performance of the list's insert method
 * 
 * @return float* An array of times in ms
 */
float* listInsertPerformance();

/**
 * @brief Measures the performance of the list's sort method
 * 
 * @return float* An array of times in ms
 */
float* listSortPerformance();

/**
 * @brief Measures the performance of the list's reverse method
 * 
 * @return float* An array of times in ms
 */
float* listReversePerformance();

/**
 * @brief Measures the performance of the list's get method
 * 
 * @return float* An array of times in ms
 */
float* listGetPerformance();

/**
 * @brief Measures the performance of the list's search method
 * 
 * @return float* An array of times in ms
 */
float* listSearchPerformance();

/**
 * @brief Measures the performance of the list's remove method
 * 
 * @return float* An array of times in ms
 */
float* listRemovePerformance();

/**
 * @brief Measures the performance of the dynamic array's add method
 * 
 * @return float* An array of times in ms
 */
float* dynarrAddPerformance();

/**
 * @brief Measures the performance of the dynamic array's insert method
 * 
 * @return float* An array of times in ms
 */
float* dynarrInsertPerformance();

/**
 * @brief Measures the performance of the dynamic array's sort method
 * 
 * @return float* An array of times in ms
 */
float* dynarrSortPerformance();

/**
 * @brief Measures the performance of the dynamic array's reverse method
 * 
 * @return float* An array of times in ms
 */
float* dynarrReversePerformance();

/**
 * @brief Measures the performance of the dynamic array's get method
 * 
 * @return float* An array of times in ms
 */
float* dynarrGetPerformance();

/**
 * @brief Measures the performance of the dynamic array's search method
 * 
 * @return float* An array of times in ms
 */
float* dynarrSearchPerformance();

/**
 * @brief Measures the performance of the dynamic array's remove method
 * 
 * @return float* An array of times in ms
 */
float* dynarrRemovePerformance();

#endif