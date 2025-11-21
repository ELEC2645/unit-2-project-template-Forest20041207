#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define PI 3.141592654
#define MAX_INPUT_LEN 100

//Function declarations
static void show_calculator_menu();
static void clear_input_buffer();
static double get_input());
static int get_choice(int choice);
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
    static double log(double x);
    static double square_root(double x);

    //Unit conversions
    static double celsius_to_fahrenheit(double celsius);
    static double fahrenheit_to_celsius(double fahrenheit);
    static double meters_to_feet(double meters);
    static double feet_to_meters(double feet);
    static double radians_to_degrees(double radians);
    static double degrees_to_radians(double degrees);



void Scientific_calculator(void) {
    printf("\n>> Scientific calculator\n");
    while (1) {
        show_calculator_menu();
        int choice = get_input();
        get_choice(int choice);
        
        
    return 0;
}


//Functions
 void show_calculator_menu() {
    printf("=== Main Menu ===\n");
    printf("1. Basic Calculator (+, -, *, /, ^)\n");
    printf("2. Scientific Functions (sin, cos, tan, log, sqrt)\n");
    printf("3. Unit Conversions\n");
    printf("0. Exit\n");
}
   
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int get_input(void)
{
    enum { MENU_ITEMS = 4 };   /* 1..4 = items, 5 = Exit */
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
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } else {
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
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\n");
    }


// Basic calculator
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed!\n");
        return 0;
    }
    return a / b;
}

double power(double base, double exponent) {
    return pow(base, exponent);
}

void basic_calculator() {
    printf("\n=== Basic Calculator ===\n");
    
    double num1;
    double num2;
    double result;

    printf("Enter the number1:\n");
    scanf("%f", &num1);
    printf("Enter the number2:\n");
    scanf("%f", &num2);
    
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Power (^)\n");
    
    int operation;
    printf("\nSelect item: ");
    scanf("%d", &operation); 
    switch (operation) {
        case 1:
            result = add(num1, num2);
            printf("Result: %.6f + %.6f = %.6f\n", num1, num2, result);
            break;
        case 2:
            result = subtract(num1, num2);
            printf("Result: %.6f - %.6f = %.6f\n", num1, num2, result);
            break;
        case 3:
            result = multiply(num1, num2);
            printf("Result: %.6f * %.6f = %.6f\n", num1, num2, result);
            break;
        case 4:
            result = divide(num1, num2);
            if (num2 != 0) {
                printf("Result: %.6f / %.6f = %.6f\n", num1, num2, result);
            }
            break;
        case 5:
            result = power(num1, num2);
            printf("Result: %.6f ^ %.6f = %.6f\n", num1, num2, result);
            break;
        default:
            printf("Invalid operation selection.\n");
    }
}


    /* you can call a function from here that handles menu 1 */
}

