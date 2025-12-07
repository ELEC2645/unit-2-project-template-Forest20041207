#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define PI 3.141592654
#define MAX_INPUT_LEN 100


// Function declaration
void Scientific_calculator(void);
static void show_calculator_menu();
static int get_input();
static void get_choice(int choice);
static void basic_calculator();
static void scientific_functions();
static void unit_conversions();
static int  is_integer(const char *s);
static double safe_double();
static int safe_int_range(int min, int max);


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

//Functions
void Scientific_calculator(void) {
    for(;;) {
       show_calculator_menu();
        int choice = get_input();
        get_choice(choice);
        if (choice == 4) {
        printf("Return to Main Menu...\n");
        return;
    }
    }
}


static void show_calculator_menu(void)
{
    printf("\n----------- Scientific Calculator -----------\n");
    printf("1. Basic Calculator\n");
    printf("2. Scientific Functions\n");
    printf("3. Unit Conversions\n");
    printf("4. Return to Main Menu\n");
    printf("--------------------------------------------\n");
    printf("Select an option: ");
}

   

static int is_integer(const char *s)
{
    if (!s || !*s) return 0;

    /* optional sign */
    if (*s == '+' || *s == '-') s++;

    /* must have at least one digit */
    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}


static int get_input(void)
{
    enum { MENU_ITEMS = 4 };   
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
            valid_input = 0;
        } 
        else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } 
            else {
                printf("Invalid menu item!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static void get_choice(int choice)
{
    switch (choice) {
            case 1:
                basic_calculator();
                break;
            case 2:
                scientific_functions();
                break;
            case 3:
                unit_conversions();
                break;
            case 4:
                printf("Thank you for using the Scientific Calculator. \n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }


// Basic calculator
static double add(double a, double b) {
    return a + b;
}

static double subtract(double a, double b) {
    return a - b;
}

static double multiply(double a, double b) {
    return a * b;
}

static double divide(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed!\n");
        return 0;
    }
    return a / b;
}

static double power(double base, double exponent) {
    return pow(base, exponent);
}


static void basic_calculator() {
    printf("\n------ Basic Calculator ------\n");
    
    double num1;
    double num2;
    double result;

    printf("\nEnter the number1:");
    num1 = safe_double();
    printf("\nEnter the number2:");
    num2 = safe_double();
    
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Power (^)\n");
    
    int operation;
    printf("\nSelect item: ");
    operation = safe_int_range(1, 5);
    switch (operation) {
        case 1:
            result = add(num1, num2);
            printf("\n----------- Calculation Result -----------\n");
            printf("%.6f + %.6f = %.6f\n", num1, num2, result);
            printf("-----------------------------------------\n");
            break;
        case 2:
            result = subtract(num1, num2);
            printf("\n----------- Calculation Result -----------\n");
            printf("%.6f + %.6f = %.6f\n", num1, num2, result);
            printf("-----------------------------------------\n");
            break;
        case 3:
            result = multiply(num1, num2);
            printf("\n----------- Calculation Result -----------\n");
            printf("%.6f + %.6f = %.6f\n", num1, num2, result);
            printf("-----------------------------------------\n");
            break;
        case 4:
            result = divide(num1, num2);
            if (num2 != 0) {
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f + %.6f = %.6f\n", num1, num2, result);
                printf("-----------------------------------------\n");
            }
            break;
        case 5:
            result = power(num1, num2);
            printf("\n----------- Calculation Result -----------\n");
            printf("%.6f + %.6f = %.6f\n", num1, num2, result);
            printf("-----------------------------------------\n");
            break;
        default:
            printf("Invalid operation selection.\n");
    }
}

//Scientific functions
static double sine(double angle) {
    return sin(degrees_to_radians(angle));
}


static double cosine(double angle) {
    return cos(degrees_to_radians(angle));
}


static double tangent(double angle) {
    double angle_radians = degrees_to_radians(angle);
    if (fabs(fmod(angle, 180.0)) == 90.0) {
        printf("Tangent is undefined for angle %.1f°！\n", angle);
        return 0;
    }
    return tan(angle_radians);
}

static double logarithm(double x) {
    if (x <= 0) {
        printf("Log is only defined for positive numbers!\n");
        return 0;
    }
    return log10(x);
}


static double square_root(double x) {
    if (x < 0) {
        printf("Square root is not defined for negative numbers!\n");
        return 0;
    }
    return sqrt(x);
}


static void scientific_functions() {
    int function;
    double input, result;

    printf("\n------- Scientific Functions ------\n");
    printf("1. Sine (sin)\n");
    printf("2. Cosine (cos)\n");
    printf("3. Tangent (tan)\n");
    printf("4. Logarithm base 10 (log)\n");
    printf("5. Square Root (sqrt)\n");
    printf("\nSelect item: ");
    function = safe_int_range(1, 5);
    
    
    
    switch (function) {
        case 1:
            printf("\nEnter the number in degrees:");
            input = safe_double();
            result = sine(input);
            printf("\n----------- Calculation Result -----------\n");
            printf("sin(%.6f°) = %.6f\n", input, result);
            printf("-----------------------------------------\n");
            break;
        case 2:
            printf("\nEnter the number in degrees:");
            input = safe_double();
            result = cosine(input);
            printf("\n----------- Calculation Result -----------\n");
            printf("cos(%.6f°) = %.6f\n", input, result);
            printf("-----------------------------------------\n");
            break;
        case 3:
            printf("\nEnter the number in degrees:");
            input = safe_double();
            result = tangent(input);
            printf("\n----------- Calculation Result -----------\n");
            printf("tan(%.6f°) = %.6f\n", input, result);
            printf("-----------------------------------------\n");
            break;
        case 4:
            printf("\nEnter the number:");
            input = safe_double();
            result = logarithm(input);
            if (input > 0) {
                printf("\n----------- Calculation Result -----------\n");
                printf("log10(%.6f°) = %.6f\n", input, result);
                printf("-----------------------------------------\n");
            }
            break;
        case 5:
            printf("\nEnter the number:");
            input = safe_double();
            result = square_root(input);
            if (input >= 0) {
                printf("\n----------- Calculation Result -----------\n");
                printf("sqrt(%.6f°) = %.6f\n", input, result);
                printf("-----------------------------------------\n");
            }
            break;
        default:
            printf("Invalid function selection.\n");
    }
}

//Unit conversions
static double celsius_to_fahrenheit(double celsius) {
    return (celsius * 9.0/5.0) + 32.0;
}

static double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0/9.0;
}

static double meters_to_feet(double meters) {
    return meters * 3.28084;
}

static double feet_to_meters(double feet) {
    return feet / 3.28084;
}

static double radians_to_degrees(double radians) {
    return radians * (180.0 / PI);
}

static double degrees_to_radians(double degrees) {
    return degrees * (PI / 180.0);
}

static void unit_conversions() {
    int conversion;
    double input, result;
    printf("\n------ Unit Conversions ------\n");
    printf("1. Temperature (Celsius ↔ Fahrenheit)\n");
    printf("2. Length (Meters ↔ Feet)\n");
    printf("3. Angles (Degrees ↔ Radians)\n");
    printf("\nSelect conversion type:");
    conversion = safe_int_range(1, 3);
    
    switch (conversion) {
        case 1:
            printf("1. Celsius to Fahrenheit\n");
            printf("2. Fahrenheit to Celsius\n");
            printf("\nSelect conversion type:");
            int conversion2;
            conversion2 = safe_int_range(1, 2);
            
            if (conversion2 == 1) {
                printf("\nEnter temperature in Celsius:");
                input = safe_double();
                result = celsius_to_fahrenheit(input);
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f°C = %.6f°F\n", input, result);
                printf("-----------------------------------------\n");
            } 
            else if (conversion2 == 2) {
                printf("\nEnter temperature in Fahrenheit:");
                input = safe_double();
                result = fahrenheit_to_celsius(input);
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f°F = %.6f°C\n", input, result);
                printf("-----------------------------------------\n");
            } 
            else {
                printf("Invalid choice.\n");
            }
            break;
        

        case 2:
            printf("1. Meters to Feet\n");
            printf("2. Feet to Meters\n");
            printf("\nSelect conversion type:");
            int conversion3;
            conversion3 = safe_int_range(1, 2);
        
            if (conversion3 == 1) {
                printf("\nEnter length in meters:");
                input = safe_double();
                result = meters_to_feet(input);
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f meters = %.6f feet\n", input, result);
                printf("-----------------------------------------\n");
            } 
            else if (conversion3 == 2) {
                printf("\nEnter length in Feet:");
                input = safe_double();
                result = feet_to_meters(input);
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f feet = %.6f meters\n", input, result);
                printf("-----------------------------------------\n");
                
            } 
            else {
                printf("Invalid choice.\n");
            }
            break;
        

        case 3:
            printf("1. Degrees to Radians\n");
            printf("2. Radians to Degrees\n");
            printf("\nSelect conversion type:");
            int conversion4;
            conversion4 = safe_int_range(1, 2);
            
            if (conversion4 == 1) {
                printf("\nEnter angle in Degrees:");
                input = safe_double();
                result = degrees_to_radians(input);
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f° = %.6f radians\n", input, result);
                printf("-----------------------------------------\n");
            } 
            else if (conversion4 == 2) {
                printf("\nEnter angle in Radians:");
                input = safe_double();
                result = radians_to_degrees(input);
                printf("\n----------- Calculation Result -----------\n");
                printf("%.6f radians = %.6f°\n", input, result);
                printf("-----------------------------------------\n");
            } 
            else {
                printf("Invalid choice.\n");
            }
            break;

        default:
            printf("Invalid conversion selection.\n");
    }
}


//Protection
double safe_double()
{
    double value;
    char c;

    while (scanf("%lf", &value) != 1)
    {
        printf("\nError: please enter a valid number:");
        while ((c = getchar()) != '\n' && c != EOF);
    }
    while ((c = getchar()) != '\n' && c != EOF);

    return value;
}


int safe_int_range(int min, int max)
{
    double temp;    
    char c;

    while (scanf("%lf", &temp) != 1 || temp != (int)temp || temp < min || temp > max)
    {
        printf("\nError: please input an integer between %d and %d:", min, max);
        while ((c = getchar()) != '\n' && c != EOF);
    }

    while ((c = getchar()) != '\n' && c != EOF);

    return (int)temp;
}

   


