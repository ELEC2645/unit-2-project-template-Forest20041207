#include <stdio.h>
#include <math.h>

//Definition
#define Square_root_3 1.732050808
#define PI 3.141592654 



// Function declaration
void Three_phase_power_calculator(void);
static void calculate_three_phase_power(void);
static double calculate_power_factor(double angle_degrees);
static void print_power_with_units(double value, const char* unit);
static double safe_double(void);
static int safe_int_range(int min, int max);



//Functions
static double calculate_power_factor(double angle_degrees) {
    double angle_radians = angle_degrees * (PI / 180.0);
    return cos(angle_radians);
}


static void print_power_with_units(double value, const char* unit) {
    double absolute_value = fabs(value); 
    
    if (absolute_value >= 1000000000.0) {
        printf("%.3f G%s\n", value / 1000000000.0, unit);
    } 
    else if (absolute_value >= 1000000.0) {
        printf("%.3f M%s\n", value / 1000000.0, unit);
    } 
    else if (absolute_value >= 1000.0) {
        printf("%.3f k%s\n", value / 1000.0, unit);
    } 
    else {
        printf("%.3f %s\n", value, unit);
    }
}


static void calculate_three_phase_power(void) {
    int connection_choice;
    double line_voltage, line_current, phase_angle;

    printf("Select Connection Type:\n");
    printf("1. Star Connection (Y)\n");
    printf("2. Delta Connection (Δ)\n");
    printf("Enter choice: ");
    connection_choice = safe_int_range(1, 2);

    printf("Enter Line Voltage (V): ");
    line_voltage = safe_double();
    while (line_voltage <= 0) {
        printf("Voltage must be positive. Enter again: ");
        line_voltage = safe_double();
    }
    
    printf("Enter Line Current (A): ");
    line_current = safe_double();
    while (line_current <= 0) {
        printf("Current must be positive. Enter again: ");
        line_current = safe_double();
    }

    printf("Enter Phase Angle φ (degrees, positive for Inductive, negative for Capacitive): ");
    phase_angle = safe_double();

    double power_factor = calculate_power_factor(phase_angle);
    double cos_phi = power_factor;
    double sin_phi = sin(phase_angle * (PI / 180.0));
    
    double apparent_power_S = Square_root_3 * line_voltage * line_current;
    
    double active_power_P = apparent_power_S * cos_phi;
    
    double reactive_power_Q = apparent_power_S * sin_phi;
    
    printf("\nThree-Phase Power Calculation Results\n");
    printf("Connection Type: ");
    if (connection_choice == 1) {
        printf("Star (Y)\n");
    } else {
        printf("Delta (Δ)\n");
    }
    
    printf("Power Factor (PF): %.4f ", fabs(cos_phi)); 
    if (phase_angle > 0) {
        printf("(Lagging/Inductive)\n");
    } 
    else if (phase_angle < 0) {
        printf("(Leading/Capacitive)\n");
    } 
    else {
        printf("(Resistive)\n");
    }
    
    printf("\n----------- Three-Phase Power Result -----------\n");
    printf("Apparent Power (S): ");
    print_power_with_units(apparent_power_S, "VA");
    printf("Active Power   (P): ");
    print_power_with_units(active_power_P, "W");
    printf("Reactive Power (Q): ");
    print_power_with_units(reactive_power_Q, "VAR");
    printf("-----------------------------------------------\n");

    
    
    if (connection_choice == 1) { 
        printf("Phase Voltage: %.3f V\n", line_voltage / Square_root_3);
        printf("Phase Current: %.3f A\n", line_current);
    } 
    else { 
        printf("Phase Voltage: %.3f V\n", line_voltage);
        printf("Phase Current: %.3f A\n", line_current / Square_root_3);
    }
}


void Three_phase_power_calculator(void) {
    int choice = 0;
    
    do {
        printf("\n----------- Three-Phase Power Calculator -----------\n");
        printf("1. Start Calculation\n");
        printf("2. Return to Main Menu\n");
        printf("----------------------------------------------------\n");
        printf("Select an option: ");

        choice = safe_int_range(1, 2);

        switch (choice) {
            case 1:
                calculate_three_phase_power();
                break;
            case 2:
                printf("Thank you for using the Three-Phase Power Calculator.\nReturn to Main Menu...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 2);
}



static double safe_double(void) {
    double value;
    char c;

    while (scanf("%lf", &value) != 1) {
        printf("Invalid input! Enter a number: ");
        while ((c = getchar()) != '\n' && c != EOF);
    }

    while ((c = getchar()) != '\n' && c != EOF);
    return value;
}


static int safe_int_range(int min, int max) {
    double temp;
    char c;

    while (scanf("%lf", &temp) != 1 || temp != (int)temp || (int)temp < min || (int)temp > max)
    {
        printf("Enter an integer between %d and %d: ", min, max);
        while ((c = getchar()) != '\n' && c != EOF);
    }

    while ((c = getchar()) != '\n' && c != EOF);
    return (int)temp;
}