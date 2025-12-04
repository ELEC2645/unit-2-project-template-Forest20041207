#ifndef SCIENTIFIC_CALCULATOR_H
#define SCIENTIFIC_CALCULATOR_H

// Function declaration
void Scientific_calculator(void);
static void show_calculator_menu();
static void clear_input_buffer();
static int get_input();
static void get_choice(int choice);
static void basic_calculator();
static void scientific_functions();
static void unit_conversions();
static int  is_integer(const char *s);

    //Basic calculator
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
    static double power(double base, double exponent);

    //Scientific functions
    static double sine(double angle);
    static double cosine(double angle);
    static double tangent(double angle);
    static double logarithm(double x);
    static double square_root(double x);

    //Unit conversions
    static double celsius_to_fahrenheit(double celsius);
    static double fahrenheit_to_celsius(double fahrenheit);
    static double meters_to_feet(double meters);
    static double feet_to_meters(double feet);
    static double radians_to_degrees(double radians);
    static double degrees_to_radians(double degrees);


#endif