#ifndef BASIC_CIRCUIT_ANALYSER_H
#define BASIC_CIRCUIT_ANALYSER_H

// Function declaration
void Basic_circuit_analyser();
static void analyse_series_circuit(void);
static void analyse_parallel_circuit(void);
static void analyse_mixed_circuit(void);
static void calculate_current(double resistance);
static void print_resistance_with_units(double resistance);
static double calculate_series_resistance(double* resistors, int number);
static double calculate_parallel_resistance(double* resistors, int number);


#endif